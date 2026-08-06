#include <stdio.h>
#include <nds.h>
#include "player.h"
#include "mctypes.h"
#include "keyAssignation.h"

void loadKeyAssignation(player_t *player,vec3_t *Direction){
    bool specialmode = false;
    if(keysHeld() & KEY_L){
      specialmode = true;
    }
    if(keysUp() & KEY_L){
      specialmode = false;
    }
    if (keysHeld() & KEY_LEFT) {
      movePlayer(player, (vec3_t){
        .x = -(cosf(player->Camera.yaw) * P_SPEED),
        .y = 0.0f,
        .z = -(sinf(player->Camera.yaw) * P_SPEED)
      });
    }
    if (keysHeld() & KEY_RIGHT) {
      movePlayer(player, (vec3_t){
        .x = cosf(player->Camera.yaw) * P_SPEED,
        .y = 0.0f,
        .z = sinf(player->Camera.yaw) * P_SPEED
      });
    }
    if (keysHeld() & KEY_UP) {
      movePlayer(player, (vec3_t){
        .x = sinf(player->Camera.yaw) * P_SPEED,
        .y = 0.0f,
        .z = -cosf(player->Camera.yaw) * P_SPEED
      });
    }
    if (keysHeld() & KEY_DOWN) {
      movePlayer(player, (vec3_t){
        .x = -(sinf(player->Camera.yaw) * P_SPEED),
        .y = 0.0f,
        .z = cosf(player->Camera.yaw) * P_SPEED
      });
    }
    if(keysHeld() & KEY_Y){
      player->Camera.yaw -= P_SENSI;
    }
    if(keysHeld() & KEY_A){
      player->Camera.yaw += P_SENSI;
    }
    if(keysHeld() & KEY_B){
      if( specialmode != true && sinf(player->Camera.pitch) > -MAX_ANGLE){
        player->Camera.pitch -= P_SENSI;
      }
    }
    if(keysHeld() & KEY_X){
      if(sinf(player->Camera.pitch) < MAX_ANGLE){
        player->Camera.pitch += P_SENSI;
      }
    }
    if((keysHeld() & KEY_L) && (keysUp() & KEY_R)){
      lcdMainOnBottom();
    }
    if(keysUp() & KEY_START){
      systemShutDown();
    }
    if((keysHeld() & KEY_L) && ( keysHeld() & KEY_B)){
      movePlayer(player,(vec3_t){.x=0,.y=P_FLYSPEED,.z=0});
    }
    if((keysHeld() & KEY_L) && ( keysHeld() & KEY_SELECT)){
      movePlayer(player,(vec3_t){.x=0,.y=-P_FLYSPEED,.z=0});
    }
}