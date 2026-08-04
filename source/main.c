#include <stdbool.h>
#include <stdlib.h>
#include <nds.h>
#include <stdio.h>
#include "mesh.h"
//#include "main.h"
#include "player.h"
#include "ChunkStruct.h"
#include "keyAssignation.h"
#include "Blocks.h"
#include "stone.h"

player_t Joueur;

const float vitesse = 0.08f;
const float vitesseRotation = 0.06f;

int main() {
  setPlayer(&Joueur);
  InitBlocks();
  powerOn(POWER_ALL_2D | POWER_3D_CORE | POWER_MATRIX);
  videoSetMode(MODE_0_3D);
  glInit();
  glClearColor(10, 20, 31, 31); // fond bleu ciel
  consoleDemoInit();
  BG_PALETTE_SUB[0] = RGB15(10,20,10);
  glEnable(GL_ANTIALIAS);
  glViewport(0, 0, SCREEN_W - 1, SCREEN_H - 1);
  glMatrixMode(GL_PROJECTION);
  gluPerspective(70, (float)SCREEN_W / (float)SCREEN_H, 0.1, 40);


  chunk_t chunkTest = {
    .position.x = 1, .position.z = 0
  };

  chunk_t chunkTest2 = {
    .position.x = 0, .position.z = 0
  };

  initChunk(&chunkTest,DIRT);
  initChunk(&chunkTest2,GRASS);

  //movePlayer(&Joueur, (vec3_t){.x=0,.y=1,.z=0});
  printf("\n\t\tMinecraft DS Edition\n");
  while (pmMainLoop()) {
    vec3_t Direction = getDir(Joueur.Camera);
    scanKeys();
    loadKeyAssignation(&Joueur,&Direction,vitesse,vitesseRotation);
    glMatrixMode(GL_MODELVIEW); // reset complet chaque frame
    glLoadIdentity();

    glLight(
      0,
      RGB15(31,31,31),      // Soleil bien blanc
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

    //drawSpecialCube(false);
    hitbox_t cubetest = {.x = 0, .y = 0, .z = 0, .w = 1, .h = 1};
    drawCube(false,(rgb_t){.r=31,.g=31,.b=31});

    if(checkCollision(Joueur.hitbox,cubetest)){
      printf("en collision\n");
    }

    RenderChunk(&chunkTest,gBlocks);

    // if(chunkTest2.position.x*L_CHUNK <= Joueur.Position.x && Joueur.Position.x <= chunkTest2.position.x*L_CHUNK + L_CHUNK &&
    //     chunkTest2.position.z*L_CHUNK <= Joueur.Position.z && Joueur.Position.z <= chunkTest2.position.z*L_CHUNK + L_CHUNK){
    //       RenderChunk(&chunkTest2,gBlocks);
    //     }
    //consoleClear();
    glFlush(0);
    swiWaitForVBlank();
  }
  return EXIT_SUCCESS;
}