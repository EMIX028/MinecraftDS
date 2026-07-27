#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <nds.h>
#include <stdio.h>
#include "mesh.h"
#include "main.h"


camera_t Camera = {
                    .position.x = 0.5, .position.y = 1.5, .position.z = 0.0,
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

  while (pmMainLoop()) {
    vec3 Direction = getDir(Camera);
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
      Camera.position.x += sinf(Camera.yaw) * vitesse;
      Camera.position.z += -cosf(Camera.yaw) * vitesse;
    }
    if (k & KEY_DOWN) {
      Camera.position.x -= sinf(Camera.yaw) * vitesse;
      Camera.position.z -= -cosf(Camera.yaw) * vitesse;
    }
    if(k & KEY_Y){
      Camera.yaw -= vitesseRotation;
    }
    if(k & KEY_A){
      Camera.yaw += vitesseRotation;
    }
    if(k & KEY_B){
      //printf("pitch : %f\n",sinf(Camera.pitch));
      if(sinf(Camera.pitch) > -MAX_ANGLE){
        Camera.pitch -= vitesseRotation;
      }
    }
    if(k & KEY_X){
      // printf("pitch : %f\n",sinf(Camera.pitch));
      if(sinf(Camera.pitch) < MAX_ANGLE){
        Camera.pitch += vitesseRotation;
      }
    }
    if(keysDown() & KEY_L){
      printf("point x: %d, y: %d, z: %d\n",(int)round(Camera.position.x + Direction.x),
                        (int)round(Camera.position.y + Direction.y),
                        (int)round(Camera.position.z + Direction.z));
    }
    if(keysUp() & KEY_L){
      consoleClear();
    }
    //touches
    glMatrixMode(GL_MODELVIEW); // reset complet chaque frame
    glLoadIdentity();

    gluLookAt(
      Camera.position.x, Camera.position.y, Camera.position.z,
      
      Camera.position.x + Direction.x, Camera.position.y +Direction.y, Camera.position.z + Direction.z,

      0.0f, 1.0f, 0.0f
    );

    drawCube(true);

    glPushMatrix();
      glTranslatef32(0.0,floattof32(-1.0),floattof32(1.0));
      drawPierre(true);
    glPopMatrix(1);

    glFlush(0);
    swiWaitForVBlank();
  }
  return EXIT_SUCCESS;
}


vec3 getDir(camera_t cam){
  vec3 dir;
  dir.x = sinf(cam.yaw)*cosf(cam.pitch);
  dir.y = sinf(cam.pitch);
  dir.z = -cosf(cam.yaw)*cosf(cam.pitch);
  return dir;
}