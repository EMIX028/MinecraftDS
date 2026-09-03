#include "keyAssignation.h"

bool mainLCD = false;


void loadKeyAssignation(player_t *player){
  if((keysHeld() & KEY_L) && ( keysDown() & KEY_B) && !player->isfalling){
    player->velocityY = 0.13749f;
    player->isfalling = true;
  }
  if((keysHeld() & KEY_L) && (keysDown() & KEY_X)){
      if(!mainLCD){
        lcdMainOnBottom();
        mainLCD = true;
      }
      else{
        lcdMainOnTop();
        mainLCD = false;
      }
    }
}