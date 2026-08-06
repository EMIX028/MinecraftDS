#include <stdio.h>
#include <nds.h>
#include "player.h"
#include "mctypes.h"
#include "keyAssignation.h"

void loadKeyAssignation(player_t *player,vec3_t *Direction){
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