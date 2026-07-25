#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <nds.h>
#include <stdio.h>
#include "nds/arm9/videoGL.h"
#include "../include/Untitled.h"


static float posX = 0.0f;
static float posY = 1.5f;      // hauteur des yeux
static float posZ = 2.0f;

static float angle = 0.0f;     // rotation autour de Y

const float vitesse = 0.08f;
const float vitesseRotation = 0.04f;

int main() {
  powerOn(POWER_ALL_2D | POWER_3D_CORE | POWER_MATRIX);
  videoSetMode(MODE_0_3D);
  glInit();
  consoleDemoInit();
  BG_PALETTE_SUB[0] = RGB15(4,8,25);
  glEnable(GL_ANTIALIAS);
  glViewport(0, 0, 255, 191);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70, 256.0 / 192.0, 0.1, 40);

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


  while (pmMainLoop()) {
    float dirX = sinf(angle);
    float dirZ = -cosf(angle);
    float rightX = cosf(angle);
    float rightZ = sinf(angle);
    scanKeys();
    u16 k = keysHeld();
    if (k & KEY_LEFT) {
      posX -= rightX * vitesse;
      posZ -= rightZ * vitesse;
    }
    if (k & KEY_RIGHT) {
      posX += rightX * vitesse;
      posZ += rightZ * vitesse;
    }
    if (k & KEY_UP) {
      posX += dirX * vitesse;
      posZ += dirZ * vitesse;
    }
    if (k & KEY_DOWN) {
      posX -= dirX * vitesse;
      posZ -= dirZ * vitesse;
    }
    if(k & KEY_Y){
      angle -= vitesseRotation;
    }
    if(k & KEY_A){
      angle += vitesseRotation;
    }
    if(keysUp()){
      consoleClear();
    }
    //touches
    glMatrixMode(GL_MODELVIEW);
    // CRUCIAL : reset complet chaque frame
    glLoadIdentity();

    gluLookAt(
      posX,
      posY,
      posZ,

      posX + dirX,
      posY,
      posZ + dirZ,

      0.0f,
      1.0f,
      0.0f
    );

    drawCube(false);

    glFlush(0);
    swiWaitForVBlank();
  }
  return EXIT_SUCCESS;
}


