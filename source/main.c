#include <_ansi.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "main.h"
#include "ChunkStruct.h"
#include "nds/arm9/videoGL.h"
#include "nds/system.h"
#include "player.h"
#include "Blocks.h"
#include "TextureAtlas.h"
#include "keyAssignation.h"
#include "utils.h"

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
const uint8_t RenderDistance = 2;

int8_t map = 1;

#define SIZE 4
chunk_t chunkL[SIZE] = {
  (chunk_t){.position.x = 0, .position.z = 0},
  (chunk_t){.position.x = -1, .position.z = 0},
  (chunk_t){.position.x = 0, .position.z = -1},
  (chunk_t){.position.x = -1, .position.z = -1}
};

//définition d'un TIMER et du compteur de fps
#define TIMER_TICKS_PER_SECOND (BUS_CLOCK / 1024)
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
  gluPerspective(70, (float)SCREEN_W / (float)SCREEN_H, 0.1, L_CHUNK*RenderDistance);
  

  char pseudo[PersonalData->nameLen + 1];
  void *s = PersonalData->name;
  for (uint16_t *p = s; p < (uint16_t*)s + PersonalData->nameLen; ++p) {
    pseudo[p - (uint16_t*)s] = *p;
  }
  pseudo[PersonalData->nameLen] = '\0';

  int TextureID;

  glGenTextures(1, &TextureID);
  glBindTexture(0, TextureID);

  if (glTexImage2D(
    0,
    0,
    GL_RGBA,
    TEXTURE_SIZE_256,
    TEXTURE_SIZE_256,
    0,
    TEXGEN_TEXCOORD,
    TextureAtlasBitmap
  ) == 0){
    printf("\nerreur init texture\n");
  }

  setPlayground(MAP_0);

  movePlayer(&Joueur,(vec3_t){.x = 0.0f,.y = 5.0f,.z=0.0f});

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
    glBindTexture(0, TextureID);

    subscreenAff(pseudo);
    loadPlayerMovement(&Joueur,chunkL,SIZE,gBlocks,blocks);
    loadKeyAssignation(&Joueur);

    if(keysDown() & KEY_START){
      setPlayground(powf(-1, map));
      movePlayer(&Joueur, (vec3_t){.x=-Joueur.Position.x+5.0f,
                                .y=-Joueur.Position.y+10.0f,
                                .z = -Joueur.Position.z+5.0f});
      ++map;
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

    playerInterract(&Joueur, chunkL, SIZE, indexB,gBlocks,
                    (const bool) specialmode, &majChunk, &delay);
    

    calculRenderView();

    for(uint8_t i=0;i<SIZE;i++){
      RenderChunk(&chunkL[i],gBlocks,true,&Joueur);
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






void subscreenAff(char *pseudo){
  consoleClear();
  BG_PALETTE_SUB[255] = RGB15(10, 10, 10);
  iprintf("\x1b[1;3H|Minecraft DS Edition 1.1a|");
  iprintf("\x1b[2;3H--------------------------");
  iprintf("\x1b[4;1HHey %s !",pseudo);
  iprintf("\x1b[6;1Hx:%3d y:%3d z:%3d",
          (int)Joueur.Position.x,
          (int)Joueur.Position.y,
          (int)Joueur.Position.z);
  iprintf("\x1b[8;0H Block: %s",getBlockName(indexB));
  #if DEBUG_MODE
    printf("\tyaw:%0.1f", fmodf(Joueur.Camera.yaw * (180.0f / (float)M_PI), 360.0f));
    printf("\n\tpitch : %0.3f",Joueur.Camera.pitch);
  #endif
  unsigned long wholeSec = totalTicks / TIMER_TICKS_PER_SECOND;
  unsigned long rem = totalTicks % TIMER_TICKS_PER_SECOND;
  unsigned long deciSec = (rem * 10) / TIMER_TICKS_PER_SECOND;
  iprintf("\x1b[21;0Htime : %lu.%lu s \t\t fps:%d", wholeSec, deciSec,fps);
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
    const vec3_t gravityMove = {
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

void setPlayground(int8_t type){
  switch(type){
    case DEBUG_MAP:
    default:
      for(int i = 0 ; i < SIZE ; ++i){
        initChunk(&chunkL[i],AIR);
        for(int x = 0 ; x < L_CHUNK ; ++x){
          for(int z = 0; z < L_CHUNK ; ++z){
            chunkL[i].blocks[x][0][z].id = BEDROCK;
            chunkL[i].blocks[x][1][z].id = GRASS;
          }
        }
      }
      break;
    case MAP_0:
      for(int i = 0 ; i < SIZE ; ++i){
        initChunk(&chunkL[i],AIR);
        for(int x = 0 ; x < L_CHUNK ; ++x){
          for(int z = 0; z < L_CHUNK ; ++z){
            chunkL[i].blocks[x][0][z].id = BEDROCK;
            chunkL[i].blocks[x][1][z].id = GRASS;
          }
        }
      }


      //CHUNK 0
      for(int x = 0; x < 11; ++x){
        for( int z =0; z < 11; ++z){
          chunkL[0].blocks[x][2][z].id = GRASS;
        }
      }
      for(int x = 0; x < 8; ++x){
        for( int z =0; z < 8; ++z){
          chunkL[0].blocks[x][3][z].id = GRASS;
        }
      }
      for(int x = 0; x < 4; ++x){
        for( int z =0; z < 3; ++z){
          chunkL[0].blocks[x][4][z].id = GRASS;
        }
      }
      for( int x =0; x < 10; ++x){
          chunkL[0].blocks[x][2][11].id = GRASS;
      }
      for( int x =0; x < 8; ++x){
          chunkL[0].blocks[x][2][12].id = GRASS;
      }
      for( int z =0; z < 9; ++z){
          chunkL[0].blocks[11][2][z].id = GRASS;
      }
      for( int z =0; z < 7; ++z){
          chunkL[0].blocks[12][2][z].id = GRASS;
      }
      for( int x =0; x < 5; ++x){
          chunkL[0].blocks[x][2][13].id = GRASS;
      }
      for( int z = 0; z < 7; ++z){
          chunkL[0].blocks[8][3][z].id = GRASS;
      }
      for( int x = 0; x < 6; ++x){
          chunkL[0].blocks[x][3][8].id = GRASS;
      }
      for( int x = 0; x < 5; ++x){
          chunkL[0].blocks[x][3][9].id = GRASS;
      }
      for( int x = 0; x < 3; ++x){
          chunkL[0].blocks[x][3][10].id = GRASS;
      }
      chunkL[0].blocks[0][4][3].id = GRASS;


      //CHUNK 1
      for(int x = 0; x < 14; ++x){
        for (int z = 0; z <10; ++z){
          chunkL[1].blocks[x][2][z].id = GRASS;
        }
      }
      for(int x = 8; x < 14; ++x){
        for (int z = 10; z <14; ++z){
          chunkL[1].blocks[x][2][z].id = GRASS;
        }
      }
      chunkL[1].blocks[8][2][11].id = AIR;
      chunkL[1].blocks[8][2][12].id = AIR;
      chunkL[1].blocks[8][2][13].id = AIR;
      chunkL[1].blocks[9][2][13].id = AIR;
      chunkL[1].blocks[10][2][13].id = AIR;
      chunkL[1].blocks[10][3][10].id = GRASS;
      chunkL[1].blocks[11][3][10].id = GRASS;
      chunkL[1].blocks[12][3][10].id = GRASS;
      chunkL[1].blocks[13][3][10].id = GRASS;
      chunkL[1].blocks[8][3][8].id = GRASS;
      chunkL[1].blocks[8][3][7].id = GRASS;
      chunkL[1].blocks[8][3][6].id = GRASS;
      chunkL[1].blocks[7][3][6].id = GRASS;
      chunkL[1].blocks[0][3][6].id = GRASS;
      for(int x = 0; x < 14; ++x){
        for (int z = 0; z <6; ++z){
          chunkL[1].blocks[x][3][z].id = GRASS;
        }
      }
      for(int x = 9; x < 14; ++x){
        for (int z = 6; z < 10; ++z){
          chunkL[1].blocks[x][3][z].id = GRASS;
        }
      }
      for(int x = 0; x < 14; ++x){
        for (int z = 0; z <5; ++z){
          chunkL[1].blocks[x][4][z].id = GRASS;
        }
      }
      chunkL[1].blocks[9][4][5].id = GRASS;
      chunkL[1].blocks[10][4][5].id = GRASS;
      chunkL[1].blocks[11][4][5].id = GRASS;

      chunkL[1].blocks[3][5][1].id = OAK_LOG;
      SET_ORIENTATION(chunkL[1].blocks[3][5][1].faces,top_to_Y);
      chunkL[1].blocks[3][6][1].id = OAK_LOG;
      SET_ORIENTATION(chunkL[1].blocks[3][6][1].faces,top_to_Y);
      chunkL[1].blocks[3][7][1].id = OAK_LOG;
      SET_ORIENTATION(chunkL[1].blocks[3][7][1].faces,top_to_Y);
      chunkL[1].blocks[3][8][1].id = OAK_LOG;
      SET_ORIENTATION(chunkL[1].blocks[3][8][1].faces,top_to_Y);
      chunkL[1].blocks[3][9][1].id = OAK_LOG;
      SET_ORIENTATION(chunkL[1].blocks[3][9][1].faces,top_to_Y);
      chunkL[1].blocks[3][10][1].id = OAK_LEAVE;

      chunkL[1].blocks[4][10][1].id = OAK_LEAVE;
      chunkL[1].blocks[3][10][2].id = OAK_LEAVE;
      chunkL[1].blocks[2][10][1].id = OAK_LEAVE;
      chunkL[1].blocks[3][10][0].id = OAK_LEAVE;

      chunkL[1].blocks[4][9][1].id = OAK_LEAVE;
      chunkL[1].blocks[3][9][2].id = OAK_LEAVE;
      chunkL[1].blocks[2][9][1].id = OAK_LEAVE;
      chunkL[1].blocks[3][9][0].id = OAK_LEAVE;

      for( int x = 4; x < 6; ++x){
        for(int y = 7; y < 9; ++y){
          for(int z = 0; z < 4; ++z){
            chunkL[1].blocks[x][y][z].id = OAK_LEAVE;
          }
        }
      }

      for( int x = 1; x < 3; ++x){
        for(int y = 7; y < 9; ++y){
          for(int z = 0; z < 4; ++z){
            chunkL[1].blocks[x][y][z].id = OAK_LEAVE;
          }
        }
      }
      chunkL[1].blocks[3][7][0].id = OAK_LEAVE;
      chunkL[1].blocks[3][8][0].id = OAK_LEAVE;

      chunkL[1].blocks[3][7][2].id = OAK_LEAVE;
      chunkL[1].blocks[3][8][2].id = OAK_LEAVE;
      chunkL[1].blocks[3][7][3].id = OAK_LEAVE;
      chunkL[1].blocks[3][8][3].id = OAK_LEAVE;
      
      
      break;
  }
  majChunk = true;
  calculRenderView();
}