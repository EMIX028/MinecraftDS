#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <nds.h>
#include <stdio.h>
#include "nds/arm9/videoGL.h"
#include "../include/Untitled.h"
#include "../include/main.h"
//define this because i have some library issues
#define KEY_X        (1U<<10)
#define KEY_Y        (1U<<11)

camera_t Camera = {
                    .position.x = 0.0, .position.y = 1.5, .position.z = 2.0,
                    .yaw = 0.0,
                    .pitch = 0.0
};

const float vitesse = 0.08f;
const float vitesseRotation = 0.06f;

int main() {
  powerOn(POWER_ALL_2D | POWER_3D_CORE | POWER_MATRIX);
  videoSetMode(MODE_0_3D);
  glInit();
  consoleDemoInit();
  BG_PALETTE_SUB[0] = RGB15(10,20,10);
  glEnable(GL_ANTIALIAS);
  glViewport(0, 0, 255, 191);
  glMatrixMode(GL_PROJECTION);
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

  printf("\n\t\tMinecraft DS Edition\n");

  while (pmMainLoop()) {
    position_t Direction = getDir(Camera);
    scanKeys();
    u16 k = keysHeld();
    if (k & KEY_LEFT) {
      Camera.position.x -= cosf(Camera.yaw) * vitesse;
      Camera.position.z -= sinf(Camera.yaw) * vitesse;
    }
    if (k & KEY_RIGHT) {
      Camera.position.x += cosf(Camera.yaw) * vitesse;
      Camera.position.z += sinf(Camera.yaw) * vitesse;
    }
    if (k & KEY_UP) {
      Camera.position.x += Direction.x * vitesse;
      Camera.position.z += Direction.z * vitesse;
    }
    if (k & KEY_DOWN) {
      Camera.position.x -= Direction.x * vitesse;
      Camera.position.z -= Direction.z * vitesse;
    }
    if(k & KEY_Y){
      Camera.yaw -= vitesseRotation;
    }
    if(k & KEY_A){
      Camera.yaw += vitesseRotation;
    }
    if(k & KEY_B){
      //printf("pitch : %f\n",sinf(Camera.pitch));
      if(sinf(Camera.pitch) > -0.98){
        Camera.pitch -= vitesseRotation;
      }
    }
    if(k & KEY_X){
      // printf("pitch : %f\n",sinf(Camera.pitch));
      if(sinf(Camera.pitch) < 0.98){
        Camera.pitch += vitesseRotation;
      }
    }
    //touches
    glMatrixMode(GL_MODELVIEW); // reset complet chaque frame
    glLoadIdentity();

    gluLookAt(
      Camera.position.x, Camera.position.y, Camera.position.z,
      
      Camera.position.x + Direction.x, Camera.position.y +Direction.y, Camera.position.z + Direction.z,

      0.0f, 1.0f, 0.0f
    );

    glPushMatrix();
      glScalef32(floattof32(0.5),floattof32(0.5),floattof32(0.5));
      drawCube(false);
    glPopMatrix(1);

    glPushMatrix();
      glScalef32(floattof32(0.5),floattof32(0.5),floattof32(0.5));
      glTranslatef32(0.0,floattof32(-2.0),floattof32(2.0));
      drawCube(false);
    glPopMatrix(1);



    glFlush(0);
    swiWaitForVBlank();
  }
  return EXIT_SUCCESS;
}


position_t getDir(camera_t cam){
  position_t dir;
  dir.x = sinf(cam.yaw)*cosf(cam.pitch);
  dir.y = sinf(cam.pitch);
  dir.z = -cosf(cam.yaw)*cosf(cam.pitch);
  return dir;
}