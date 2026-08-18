#include <nds.h>
#include "nds/arm9/input.h"
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
  if((keysHeld() & KEY_L) && ( keysDown() & KEY_B) && !player->isfalling){
    player->velocityY = 0.13749f;
    player->isfalling = true;
  }
  if((keysHeld() & KEY_L) && ( keysHeld() & KEY_SELECT)){
    movePlayer(player,(vec3_t){.x=0,.y=-P_FLYSPEED,.z=0});
  }
}