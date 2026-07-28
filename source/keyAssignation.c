#include <stdio.h>
#include <nds.h>
#include "player.h"
#include "mctypes.h"
#include "keyAssignation.h"

void loadKeyAssignation(camera_t *Camera,vec3_t *Direction, const float vitesse, const float sensitivity){
    if (keysHeld() & KEY_LEFT) {
      Camera->position.x -= cosf(Camera->yaw) * vitesse;
      Camera->position.z -= sinf(Camera->yaw) * vitesse;
    }
    if (keysHeld() & KEY_RIGHT) {
      Camera->position.x += cosf(Camera->yaw) * vitesse;
      Camera->position.z += sinf(Camera->yaw) * vitesse;
    }
    if (keysHeld() & KEY_UP) {
      Camera->position.x += sinf(Camera->yaw) * vitesse;
      Camera->position.z += -cosf(Camera->yaw) * vitesse;
    }
    if (keysHeld() & KEY_DOWN) {
      Camera->position.x -= sinf(Camera->yaw) * vitesse;
      Camera->position.z -= -cosf(Camera->yaw) * vitesse;
    }
    if(keysHeld() & KEY_Y){
      Camera->yaw -= sensitivity;
    }
    if(keysHeld() & KEY_A){
      Camera->yaw += sensitivity;
    }
    if(keysHeld() & KEY_B){
      //printf("pitch : %f\n",sinf(Camera->pitch));
      if(sinf(Camera->pitch) > -MAX_ANGLE){
        Camera->pitch -= sensitivity;
      }
    }
    if(keysHeld() & KEY_X){
      // printf("pitch : %f\n",sinf(Camera->pitch));
      if(sinf(Camera->pitch) < MAX_ANGLE){
        Camera->pitch += sensitivity;
      }
    }
    if(keysDown() & KEY_L){
      printf("point x: %d, y: %d, z: %d\n",(int)round(Camera->position.x + Direction->x),
                        (int)round(Camera->position.y + Direction->y),
                        (int)round(Camera->position.z + Direction->z));
    }
    if(keysUp() & KEY_L){
      consoleClear();
    }
}