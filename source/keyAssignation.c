#include <stdio.h>
#include <nds.h>
#include "player.h"
#include "mctypes.h"
#include "keyAssignation.h"

void loadKeyAssignation(player_t *player){
  if((keysHeld() & KEY_L) && (keysUp() & KEY_R)){
    lcdMainOnBottom();
  }
  if(keysDown() & KEY_START){
    systemShutDown();
  }
  if((keysHeld() & KEY_L) && ( keysHeld() & KEY_B)){
    player->velocityY = 0.25f;
    player->isfalling = true;
  }
  if((keysHeld() & KEY_L) && ( keysHeld() & KEY_SELECT)){
    movePlayer(player,(vec3_t){.x=0,.y=-P_FLYSPEED,.z=0});
  }
}