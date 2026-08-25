#include <nds.h>
#include "nds/arm9/input.h"
#include "player.h"
#include "mctypes.h"
#include "keyAssignation.h"

void loadKeyAssignation(player_t *player){
  if((keysHeld() & KEY_L) && (keysUp() & KEY_R)){
    //lcdMainOnBottom();
  }
  if((keysHeld() & KEY_L) && ( keysDown() & KEY_B) && !player->isfalling){
    player->velocityY = 0.13749f;
    player->isfalling = true;
  }
  if(keysDown() & KEY_SELECT){
    movePlayer(player, (vec3_t){.x=-player->Position.x+5.0f,
                                .y=-player->Position.y+10.0f,
                                .z = -player->Position.z+5.0f});
  }
}