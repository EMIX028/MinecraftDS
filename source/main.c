#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <nds.h>
#include <stdio.h>
#include "mctypes.h"
#include "mesh.h"
#include "main.h"
#include "player.h"
#include "ChunkStruct.h"
#include "keyAssignation.h"
#include "Blocks.h"
#include "TextureAtlas.h"


#define GRAVITY 0.008f
#define DISPLAY_DISTANCE 30
player_t Joueur;
int timer = 0;

int main() {
  setPlayer(&Joueur);
  InitBlocks();
  powerOn(POWER_ALL_2D | POWER_3D_CORE | POWER_MATRIX);
  videoSetMode(MODE_0_3D);
  glInit();
  vramSetBankA(VRAM_A_TEXTURE);
  glClearColor(10, 20, 31, 31); // fond bleu ciel
  consoleDemoInit();
  BG_PALETTE_SUB[0] = RGB15(10,17,10); //fond écran sub
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_ANTIALIAS);
  glViewport(0, 0, SCREEN_W - 1, SCREEN_H - 1);
  glMatrixMode(GL_PROJECTION);
  gluPerspective(70, (float)SCREEN_W / (float)SCREEN_H, 0.1, DISPLAY_DISTANCE);

  char pseudo[PersonalData->nameLen];
  for(int i=0;i<PersonalData->nameLen;++i){
    pseudo[i] = PersonalData->name[i];
  }

  int TextureID;

  glGenTextures(1, &TextureID);
  glBindTexture(0, TextureID);

  if (glTexImage2D(
    0,
    0,
    GL_RGB,
    TEXTURE_SIZE_64,
    TEXTURE_SIZE_64,
    0,
    TEXGEN_TEXCOORD,
    TextureAtlasBitmap
  ) == 0){
    printf("\nerreur init texture\n");
  }

  chunk_t chunk00 = {
    .position.x = 0, .position.z = 0
  };

  chunk_t chunkTest = {
    .position.x = 1, .position.z = 0
  };
  initChunk(&chunkTest,STONE);
  initChunk(&chunk00,AIR);

  chunk00.blocks[5][1][5] = DIRT;
  chunk00.blocks[5][1][6] = DIRT;
  chunk00.blocks[5][1][7] = DIRT;
  chunk00.blocks[5][2][7] = STONE;
  for(int x = 0 ; x < L_CHUNK ; ++x){
    for(int z = 0; z < L_CHUNK ; ++z){
      chunk00.blocks[x][0][z] = DIRT;
    }
  }
  chunk_t *chunk_list[] = {&chunk00,&chunkTest};
  int size = 2;
  
  movePlayer(&Joueur,(vec3_t){.x = 0.0f,.y = 1.0f,.z=0.0f});

  while (pmMainLoop()) {
    glBindTexture(0, TextureID);
    subscreenAff(pseudo);
    scanKeys();
    loadPlayerMovement(&Joueur,chunk_list,size,gBlocks,blocks);
    loadKeyAssignation(&Joueur);

    vec3_t gravityMove = {
      .x = 0.0f,
      .y = Joueur.velocityY,
      .z = 0.0f
    };

    if (canMovePlayer(&Joueur , gravityMove, chunk_list, size,gBlocks,blocks)) {
      movePlayer(&Joueur, gravityMove);
    }
    else {
      Joueur.velocityY = 0;
      Joueur.isfalling = false;
      Joueur.Position.y = (float)floor(Joueur.Position.y);
    }

    Joueur.velocityY -= GRAVITY;

    glMatrixMode(GL_MODELVIEW); // reset complet chaque frame
    glLoadIdentity();
    setCam();


    for(uint8_t i=0;i<2;i++){
      RenderChunk(chunk_list[i],gBlocks,false);
    }

    glFlush(0);
    swiWaitForVBlank();
    timer++;
  }
  return EXIT_SUCCESS;
}

void subscreenAff(char *pseudo){
  consoleClear();
  BG_PALETTE_SUB[255] = RGB15(10, 10, 10);
  iprintf("\x1b[1;5H|Minecraft DS Edition|");
  iprintf("\x1b[2;5H----------------------");
  iprintf("\x1b[4;1HBienvenue %s !",pseudo);
  iprintf("\x1b[6;1Hx:%3d y:%3d z:%3d",
          (int)Joueur.Position.x,
          (int)Joueur.Position.y,
          (int)Joueur.Position.z);
  printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\ntime : %lfs",timer/60.0);
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