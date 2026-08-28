#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <nds.h>
#include <stdio.h>
#include "calico/gba/keypad.h"
#include "calico/types.h"
#include "mctypes.h"
#include "mesh.h"
#include "main.h"
#include "nds/arm9/input.h"
#include "nds/arm9/videoGL.h"
#include "player.h"
#include "ChunkStruct.h"
#include "keyAssignation.h"
#include "Blocks.h"
#include "TextureAtlas.h"
#include <malloc.h>
#include <maxmod9.h>

#include "soundbank.h"
#include "soundbank_bin.h"


player_t Joueur;
uint8_t indexB = 1;
int delay = 0; //delay entre chaque bloc posé ou cassé
#define DELAY 11
bool majChunk = true;


chunk_t chunk00 = {
  .position.x = 0, .position.z = 0
};
chunk_t chunkTest = {
  .position.x = 1, .position.z = 0
};
chunk_t chunk01 = {
  .position.x = 0, .position.z = -1
};
chunk_t chunk02 = {
  .position.x = 1, .position.z = -1
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
  gluPerspective(70, (float)SCREEN_W / (float)SCREEN_H, 0.1, DISPLAY_DISTANCE);
  

  char pseudo[PersonalData->nameLen];
  for(int i = 0 ; i < PersonalData->nameLen ; ++i){
    pseudo[i] = PersonalData->name[i];
  }

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
  

  #define SIZE 4
  chunk_t *chunk_list[SIZE] = {&chunk00,&chunk01,&chunk02,&chunkTest};

  setPlayground(chunk_list);

  movePlayer(&Joueur,(vec3_t){.x = 5.0f,.y = 3.0f,.z=5.0f});

  mmInitDefaultMem((mm_addr)soundbank_bin);
  mm_sfxhand handle = mmEffect(SFX_WET_HANDS_DS);
  mmEffectVolume(handle, 128);

  while (pmMainLoop()) {
    struct mallinfo info = mallinfo();
    glBindTexture(0, TextureID);
    subscreenAff(pseudo,info);
    scanKeys();
    loadPlayerMovement(&Joueur,chunk_list,SIZE,gBlocks,blocks);
    loadKeyAssignation(&Joueur);
    
    if(keysDown() & KEY_START){
      setPlayground(chunk_list);
      movePlayer(&Joueur, (vec3_t){.x=-Joueur.Position.x+5.0f,
                                .y=-Joueur.Position.y+10.0f,
                                .z = -Joueur.Position.z+5.0f});
    }
    if(keysDown() & KEY_SELECT){
      break; //quitte le jeu
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

    ApplyGravity(chunk_list,SIZE);

    glMatrixMode(GL_MODELVIEW); // reset complet chaque frame
    glLoadIdentity();
    setCam();

    int targetX;
    int targetY;
    int targetZ;
    bool blockTargeted;
    vec3_t Raydir;

    Raydir = getDir(Joueur.Camera);
    vec3_t rayPos = Joueur.Camera.position;

    int previousX = 0;
    int previousY = 0;
    int previousZ = 0;
    uint8_t b;

    int previousValid = 0;

    for (float distance = 0.0f ; distance < P_REACH ; distance += 0.05f){
      rayPos.x = Joueur.Camera.position.x + Raydir.x * distance;
      rayPos.y = Joueur.Camera.position.y + Raydir.y * distance;
      rayPos.z = Joueur.Camera.position.z + Raydir.z * distance;

      int bx = (int)floorf(rayPos.x);
      int by = (int)floorf(rayPos.y);
      int bz = (int)floorf(rayPos.z);

      if ((b = getBlock(chunk_list,SIZE,bx, by, bz)) != AIR){
        targetX = bx;
        targetY = by;
        targetZ = bz;
        blockTargeted = true;
        if (previousValid && !checkCollision(Joueur.Position, Joueur.hitbox,
                                              (ivec3_t){.x=previousX,
                                                .y=previousY,
                                                .z=previousZ}, blocks)){
            
          if((keysDown() | keysHeld()) & KEY_R){
            if(specialmode != true && delay <= 0){
              setBlock(chunk_list, SIZE, previousX, previousY, previousZ, indexB);
              majChunk = true;
              delay = DELAY;
            }
          }
        }
        if((keysHeld() & KEY_L) && ((keysDown() | keysHeld()) & KEY_R)){
          if(delay <= 0 && b != BEDROCK){
            setBlock(chunk_list, SIZE, targetX, targetY, targetZ, AIR);
            majChunk = true;
            delay = DELAY;
          }
        }
        break;
      }
      else{
        blockTargeted = false;
      }
      previousX = bx;
      previousY = by;
      previousZ = bz;
      previousValid = 1;
    }

    calculRenderView(chunk_list);

    for(uint8_t i=0;i<SIZE;i++){
      RenderChunk(chunk_list[i],gBlocks,true);
    }

    if (blockTargeted) {
      drawBlockOutline(targetX, targetY, targetZ);
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
  //iprintf("\x1b[8;1HRAM heap: %lu KB",(unsigned long)(info.uordblks / 1024));
  //iprintf("\x1b[9;1HRAM free: %lu KB", (unsigned long)(info.fordblks / 1024));
  printf("\n\n\n\n\n\n\n\n\n\n\n\n\ntime : %.1f s",(float)totalTicks / TIMER_TICKS_PER_SECOND);
  printf("\t\t\tfps:%d", fps);
  iprintf("\x1b[6;18H Bloc : %d/%d",indexB,BLOCK_COUNT-1);
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

void ApplyGravity(chunk_t *chunk_list[], int size){
    vec3_t gravityMove = {
        .x = 0.0f,
        .y = Joueur.velocityY,
        .z = 0.0f
    };

    if (canMovePlayer(&Joueur, gravityMove,
                      chunk_list, size, gBlocks, blocks)){
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

void calculRenderView(chunk_t *chunk_list[]){
  if(majChunk){
    blockVisibility(chunk_list, SIZE, gBlocks);
    majChunk = false;
  }
  for(uint8_t i = 0 ; i < SIZE ; ++i){
    for(uint8_t x = 0 ; x < L_CHUNK ; ++x){
      for(uint8_t y = 0; y<H_CHUNK && y <= Joueur.Position.y ; ++y){
        for(uint8_t z = 0; z < L_CHUNK ; ++z){
          if(gBlocks[chunk_list[i]->blocks[x][0][z].id].transparent != 2){
            chunk_list[i]->blocks[x][y][z].faces &= ~FACE_BOTTOM;
          }
          chunk_list[i]->blocks[x][0][0].faces &= ~FACE_BACK;
          chunk_list[i]->blocks[x][1][0].faces &= ~FACE_BACK;

          chunk_list[i]->blocks[x][0][L_CHUNK-1].faces &= ~FACE_FRONT;
          chunk_list[i]->blocks[x][1][L_CHUNK-1].faces &= ~FACE_FRONT;

          chunk_list[i]->blocks[0][0][z].faces &= ~FACE_LEFT;
          chunk_list[i]->blocks[0][1][z].faces &= ~FACE_LEFT; 
          
          chunk_list[i]->blocks[L_CHUNK-1][0][z].faces &= ~FACE_RIGHT;
          chunk_list[i]->blocks[L_CHUNK-1][1][z].faces &= ~FACE_RIGHT;          
        }
      }
    }
  }
}

void setPlayground(chunk_t *chunk_list[]){
  for(int i = 0 ; i < SIZE ; ++i){
    initChunk(chunk_list[i],AIR);
    for(int x = 0 ; x < L_CHUNK ; ++x){
      for(int z = 0; z < L_CHUNK ; ++z){
      chunk_list[i]->blocks[x][0][z].id = BEDROCK;
      chunk_list[i]->blocks[x][1][z].id = MOSS;
      }
    }
  }
  majChunk = true;
  calculRenderView(chunk_list);
}