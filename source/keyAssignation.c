#include "keyAssignation.h"
#include <stdint.h>

bool mainLCD = false;

void loadKeyAssignation(player_t *player){
  if((keysHeld() & KEY_L) && (( keysDown() & KEY_B) || (keysHeld() & KEY_B)) && !player->isfalling){
    player->velocityY = divf32(inttof32(13749),inttof32(100000));
    player->isfalling = true;
  }
  if((keysHeld() & KEY_L) && (keysDown() & KEY_A)){
      if(player->index < BLOCK_COUNT-1){
        ++player->index;
      }
      else{
        player->index = 1;
      }
    }
    if((keysHeld() & KEY_L) && (keysDown() & KEY_Y)){
      if(player->index > 1){
        --player->index;
      }
      else{
        player->index = BLOCK_COUNT-1;
      }
    }
}