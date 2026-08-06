#include <stdbool.h>
#include <stdlib.h>
#include <nds.h>
#include <stdio.h>
#include "mesh.h"
#include "main.h"
#include "player.h"
#include "ChunkStruct.h"
#include "keyAssignation.h"
#include "Blocks.h"
#include "stone.h"

player_t Joueur;
vec3_t Direction;

int main() {
  setPlayer(&Joueur);
  InitBlocks();
  powerOn(POWER_ALL_2D | POWER_3D_CORE | POWER_MATRIX);
  videoSetMode(MODE_0_3D);
  glInit();
  vramSetBankA(VRAM_A_TEXTURE);
  glClearColor(10, 20, 31, 31); // fond bleu ciel
  consoleDemoInit();
  BG_PALETTE_SUB[0] = RGB15(10,17,10);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_ANTIALIAS);
  glViewport(0, 0, SCREEN_W - 1, SCREEN_H - 1);
  glMatrixMode(GL_PROJECTION);
  gluPerspective(70, (float)SCREEN_W / (float)SCREEN_H, 0.1, 40);

  int stoneTextureID;

  glGenTextures(1, &stoneTextureID);
  glBindTexture(0, stoneTextureID);

  if (glTexImage2D(
    0,
    0,
    GL_RGB,
    TEXTURE_SIZE_16,
    TEXTURE_SIZE_16,
    0,
    TEXGEN_TEXCOORD,
    stoneBitmap
  ) == 0){
    printf("\nerreur init texture\n");
  }

  chunk_t chunkTest = {
    .position.x = 1, .position.z = 0
  };

  initChunk(&chunkTest,DIRT);
  uint8_t compteur = 0;

  while (pmMainLoop()) {
    subscreenAff();
    vec3_t Direction = getDir(Joueur.Camera);
    scanKeys();
    loadKeyAssignation(&Joueur,&Direction);

    if(keysDown() & KEY_R){
      chunkTest.blocks[compteur][1][5] = AIR;
      ++compteur;
      printf("\n%d id block : %d",compteur,chunkTest.blocks[compteur][1][5]);
    }


    glMatrixMode(GL_MODELVIEW); // reset complet chaque frame
    glLoadIdentity();


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
      
      Joueur.Camera.position.x + Direction.x, Joueur.Camera.position.y +Direction.y, Joueur.Camera.position.z + Direction.z,

      0.0f, 1.0f, 0.0f
    );

    glBindTexture(0, stoneTextureID);

    hitbox_t cubetest = {.x = 0, .y = 0, .z = 0, .w = 1, .h = 1};
    drawCube(false);

    if(checkCollision(Joueur.hitbox,cubetest)){
      printf("\nen collision\n");
    }

    RenderChunk(&chunkTest,gBlocks);

    // if(chunkTest2.position.x*L_CHUNK <= Joueur.Position.x && Joueur.Position.x <= chunkTest2.position.x*L_CHUNK + L_CHUNK &&
    //     chunkTest2.position.z*L_CHUNK <= Joueur.Position.z && Joueur.Position.z <= chunkTest2.position.z*L_CHUNK + L_CHUNK){
    //       RenderChunk(&chunkTest,gBlocks);
    //     }
    glFlush(0);
    swiWaitForVBlank();
  }
  return EXIT_SUCCESS;
}

void subscreenAff(){
  //consoleClear();
  BG_PALETTE_SUB[255] = RGB15(10, 10, 10);
  iprintf("\x1b[1;5H|Minecraft DS Edition|");
  iprintf("\x1b[2;5H----------------------");
  iprintf("\x1b[3;1Hx:%4d y:%4d z:%4d",
          (int)Joueur.Position.x,
          (int)Joueur.Position.y,
          -(int)Joueur.Position.z);
  iprintf("\x1b[5;1HDir x:%4d y:%4d z:%4d",
          (int)(Joueur.Camera.position.x + Direction.x),
          (int)(Joueur.Camera.position.y +Direction.y),
          -(int)(Joueur.Camera.position.z + Direction.z));
}