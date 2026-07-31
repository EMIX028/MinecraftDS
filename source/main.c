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

camera_t Camera = {
                    .position.x = 0.5, .position.y = 1.5, .position.z = 0.0,
                    .yaw = 0.0,
                    .pitch = 0.0
};

const float vitesse = 0.08f;
const float vitesseRotation = 0.06f;

chunk_t test_chunk = {
  .position.x = 1.0,.position.y = 0.0,.position.z = 0.0
};

int main() {
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

  glLight(
    0,
    RGB15(20,20,20),
    floattov10(-0.5f),
    floattov10(-0.8f),
    floattov10(-1.0f)
  );
  

  glMaterialf(
    GL_AMBIENT,
    RGB15(5,5,5)
  );

  glMaterialf(
    GL_DIFFUSE,
    RGB15(31,31,31)
  );

  printf("\n\t\tMinecraft DS Edition\n");
  initChunk(&test_chunk,&pierre);
  rgb_t colorTest = {.r = 0,.g = 20, .b=0};
  while (pmMainLoop()) {
    keyboardUpdate();
    vec3_t Direction = getDir(Camera);
    scanKeys();
    loadKeyAssignation(&Camera,&Direction,vitesse,vitesseRotation);
    glMatrixMode(GL_MODELVIEW); // reset complet chaque frame
    glLoadIdentity();

    gluLookAt(
      Camera.position.x, Camera.position.y, Camera.position.z,
      
      Camera.position.x + Direction.x, Camera.position.y +Direction.y, Camera.position.z + Direction.z,

      0.0f, 1.0f, 0.0f
    );

    drawSpecialCube(false);

    glPushMatrix();
      glTranslatef32(0.0,floattof32(-1.0),floattof32(1.0));
      drawCube(true,colorTest);
    glPopMatrix(1);

    //setBlock(&pierre,true);
    setBlockFaces(&pierre,false,'L');

    drawChunk(&test_chunk,true);

    glFlush(0);
    swiWaitForVBlank();
  }
  return EXIT_SUCCESS;
}