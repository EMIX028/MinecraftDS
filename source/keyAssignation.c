#include "keyAssignation.h"
#include <stdint.h>

void loadKeyAssignation(player_t *player, u8 *GameState){
  u32 hold = keysHeld();
  u32 Kdown = keysDown();
  //u32 Kup = keysUp();
  if(Kdown & KEY_START){
    *GameState = (*GameState == PAUSED) ? RUNNING : PAUSED;
  }

  if((hold & KEY_L) && (Kdown & KEY_A)){
    if(player->index < BLOCK_COUNT-1){
      ++player->index;
    }
    else{
      player->index = 1;
    }
  }
  if((hold & KEY_L) && (Kdown & KEY_Y)){
    if(player->index > 1){
      --player->index;
    }
    else{
      player->index = BLOCK_COUNT-1;
    }
  }
}