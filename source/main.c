#include <stdio.h>
#include <math.h>
#include <malloc.h>

#include "main.h"
#include "player.h"
#include "Blocks.h"
#include "TextureAtlas.h"
#include "keyAssignation.h"

#if !DEBUG_MODE
  #include <maxmod9.h>
  #include "soundbank.h"
  #include "mm_types.h"
  #include "soundbank_bin.h"
#endif

player_t Joueur;
uint8_t indexB = 1;
int delay = 0; //delay entre chaque bloc posé ou cassé
bool majChunk = true;
uint8_t gameState = RUNNING;

#define SIZE 4
chunk_t chunkL[SIZE] = {
  (chunk_t){.position.x = 0, .position.z = 0},
  (chunk_t){.position.x = 1, .position.z = 0},
  (chunk_t){.position.x = 0, .position.z = -1},
  (chunk_t){.position.x = 1, .position.z = -1}
};

//définition d'un TIMER et du compteur de fps
#define TIMER_TICKS_PER_SECOND ((float)BUS_CLOCK / 1024)
static u32 totalTicks = 0;
static u16 previousTimer = 0;
static u16 lastFpsTimer = 0;
static int frames = 0;
static int fps = 0;


int main() {
  TIMER0_DATA = 0;
  TIMER0_CR = TIMER_ENABLE | TIMER_DIV_1024;
  previousTimer = TIMER0_DATA;
  lastFpsTimer = TIMER0_DATA;
  
  
  setPlayer(&Joueur);
  InitBlocks();
  powerOn(POWER_ALL_2D | POWER_3D_CORE | POWER_MATRIX);
  videoSetMode(MODE_0_3D);
  glInit();
  vramSetBankA(VRAM_A_TEXTURE);
  glClearColor(10, 20, 31, 31); // fond bleu ciel
  consoleDemoInit();
  BG_PALETTE_SUB[0] = RGB15(24,24,24); //fond écran sub
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_ANTIALIAS);
  glEnable(GL_BLEND);
  glViewport(0, 0, SCREEN_W - 1, SCREEN_H - 1);
  glMatrixMode(GL_PROJECTION);
  gluPerspective(70, (float)SCREEN_W / (float)SCREEN_H, 0.1, DISPLAY_DISTANCE);
  

  char pseudo[PersonalData->nameLen + 1];
  for(uint8_t i = 0 ; i < PersonalData->nameLen ; ++i){
    pseudo[i] = PersonalData->name[i];
  }
  pseudo[PersonalData->nameLen] = '\0';

  int TextureID;

  glGenTextures(1, &TextureID);
  glBindTexture(0, TextureID);

  if (glTexImage2D(
    0,
    0,
    GL_RGBA,
    TEXTURE_SIZE_64,
    TEXTURE_SIZE_64,
    0,
    TEXGEN_TEXCOORD,
    TextureAtlasBitmap
  ) == 0){
    printf("\nerreur init texture\n");
  }

  setPlayground();

  movePlayer(&Joueur,(vec3_t){.x = 5.0f,.y = 2.0f,.z=5.0f});

  #if !DEBUG_MODE
    mmInitDefaultMem((mm_addr)soundbank_bin);
    mm_sfxhand handle = mmEffect(SFX_WET_HANDS);
    mmEffectVolume(handle, 255);
  #endif  

  while (pmMainLoop()) {
    scanKeys();
    if(keysDown() & KEY_SELECT){
      if(gameState == RUNNING) { //pause switch
        gameState = PAUSED;
      } else {
        gameState = RUNNING;
      }
      ledBlink(PmLedMode_BlinkFast);
    }
    if(gameState == PAUSED){
      continue;
    }
    struct mallinfo info = mallinfo();
    glBindTexture(0, TextureID);

    subscreenAff(pseudo,info);
    loadPlayerMovement(&Joueur,chunkL,SIZE,gBlocks,blocks);
    loadKeyAssignation(&Joueur);

    if(keysDown() & KEY_START){
      setPlayground();
      movePlayer(&Joueur, (vec3_t){.x=-Joueur.Position.x+5.0f,
                                .y=-Joueur.Position.y+10.0f,
                                .z = -Joueur.Position.z+5.0f});
    }
    
    if((keysHeld() & KEY_L) && (keysDown() & KEY_A)){
      if(indexB < BLOCK_COUNT-1){
        ++indexB;
      }
      else{
        indexB = 1;
      }
    }
    if((keysHeld() & KEY_L) && (keysDown() & KEY_Y)){
      if(indexB > 1){
        --indexB;
      }
      else{
        indexB = BLOCK_COUNT-1;
      }
    }

    ApplyGravity(SIZE);

    glMatrixMode(GL_MODELVIEW); // reset complet chaque frame
    glLoadIdentity();
    setCam();

    playerInterract(&Joueur, chunkL, SIZE, indexB,
                    (const bool) specialmode, &majChunk, &delay);
    

    calculRenderView();

    for(uint8_t i=0;i<SIZE;i++){
      RenderChunk(&chunkL[i],gBlocks,true,&Joueur.Position);
    }
    

    if(delay>0){
      --delay;
    }

    glFlush(0);
    updatePerformance();
    swiWaitForVBlank();
  }
  return EXIT_SUCCESS;
}






void subscreenAff(char *pseudo,struct mallinfo info){
  consoleClear();
  BG_PALETTE_SUB[255] = RGB15(10, 10, 10);
  iprintf("\x1b[1;3H|Minecraft DS Edition 1.0a|");
  iprintf("\x1b[2;3H--------------------------");
  iprintf("\x1b[4;1HHey %s !",pseudo);
  iprintf("\x1b[6;1Hx:%3d y:%3d z:%3d",
          (int)Joueur.Position.x,
          (int)Joueur.Position.y,
          (int)Joueur.Position.z);
  iprintf("\x1b[8;1H Block: %s",getBlockName(indexB));
  #if DEBUG_MODE
    iprintf("\x1b[9;1HRAM heap: %lu KB",(unsigned long)(info.uordblks / 1024));
    iprintf("\x1b[10;1HRAM free: %lu KB", (unsigned long)(info.fordblks / 1024));
  #endif
  printf("\n\n\n\n\n\n\n\n\n\n\n\n\ntime : %.1f s",(float)totalTicks / TIMER_TICKS_PER_SECOND);
  printf("\t\t\tfps:%d", fps);
}

void setCam(){
  glLight(
      0,
      RGB15(31,31,31),
      floattov10(-0.5f),
      floattov10(-1.0f),
      floattov10(-0.3f)
    );

    glMaterialf(GL_AMBIENT, RGB15(15,15,15));
    glMaterialf(GL_DIFFUSE, RGB15(31,31,31));

    gluLookAt(
      Joueur.Camera.position.x, Joueur.Camera.position.y, Joueur.Camera.position.z,
      
      Joueur.Camera.position.x + Joueur.Direction.x, Joueur.Camera.position.y +Joueur.Direction.y, Joueur.Camera.position.z + Joueur.Direction.z,

      0.0f, 1.0f, 0.0f
    );
}

void ApplyGravity(int size){
    vec3_t gravityMove = {
        .x = 0.0f,
        .y = Joueur.velocityY,
        .z = 0.0f
    };

    if (canMovePlayer(&Joueur, gravityMove,
                      chunkL, size, gBlocks, blocks)){
        movePlayer(&Joueur, gravityMove);
    }
    else{
        if (Joueur.velocityY < 0.0f){
            Joueur.velocityY = 0.0f;
            Joueur.isfalling = false;
            Joueur.Position.y = floor(Joueur.Position.y);
        }
        else if (Joueur.velocityY > 0.0f){
            Joueur.velocityY = 0.0f;
        }
    }
    Joueur.velocityY -= GRAVITY;
}

void updatePerformance(void){
  //fonction bricoler rapidement avec l'IA
  u16 now = TIMER0_DATA;

  // Temps écoulé depuis la dernière frame
  totalTicks += (u16)(now - previousTimer);

  previousTimer = now;

  // Nombre de frames calculées
  frames++;

  // Une vraie seconde s'est écoulée
  if ((u16)(now - lastFpsTimer) >= TIMER_TICKS_PER_SECOND){
    fps = frames;
    frames = 0;
    lastFpsTimer = now;
  }
}

void calculRenderView(){
  if(majChunk){
    blockVisibility(chunkL, SIZE, gBlocks);
    majChunk = false;
  }
}

void setPlayground(){
  for(int i = 0 ; i < SIZE ; ++i){
    initChunk(&chunkL[i],AIR);
    for(int x = 0 ; x < L_CHUNK ; ++x){
      for(int z = 0; z < L_CHUNK ; ++z){
      chunkL[i].blocks[x][0][z].id = BEDROCK;
      chunkL[i].blocks[x][1][z].id = MOSS;
      }
    }
  }
  majChunk = true;
  calculRenderView();
}