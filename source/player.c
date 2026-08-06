#include "player.h"
#include <nds.h>

void setPlayer(player_t *player){
  player->Position.x = 0.5f;
  player->Position.y = 0.0f;
  player->Position.z = 0.5f;
  player->Camera.position.x = 0.5;
  player->Camera.position.y = 1.5;
  player->Camera.position.z = 0.0;
  player->Camera.yaw = 0.0;
  player->Camera.pitch = 0.0;
  player->hitbox.x = 0.0f;
  player->hitbox.y = 0.0f;
  player->hitbox.z = 0.0f;
  player->hitbox.w = 1.0f;
  player->hitbox.h = 2.0f;
  player->hitbox.d = 1.0f;
}

void movePlayer(player_t *player, vec3_t d){
  player->Position.x += d.x;
  player->Position.y += d.y;
  player->Position.z += d.z;
  player->Camera.position.x += d.x;
  player->Camera.position.y += d.y;
  player->Camera.position.z += d.z;
  player->hitbox.x += d.x;
  player->hitbox.w += d.x;
  player->hitbox.y += d.y;
  player->hitbox.h += d.y;
  player->hitbox.z += d.z;
}

vec3_t getDir(camera_t cam){
  vec3_t dir;
  dir.x = sinf(cam.yaw)*cosf(cam.pitch);
  dir.y = sinf(cam.pitch);
  dir.z = -cosf(cam.yaw)*cosf(cam.pitch);
  return dir;
}

bool checkCollision(hitbox_t a, hitbox_t b){
    return (
      a.x < b.x + b.w &&
      a.x + a.w > b.x &&

      a.y < b.y + b.h &&
      a.y + a.h > b.y &&

      a.z < b.z + b.d &&
      a.z + a.d > b.z
    );
}

void loadPlayerMovement(player_t *player,vec3_t *Direction){
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
    if(specialmode != true){
      player->Camera.yaw -= P_SENSI;
    }
  }
  if(keysHeld() & KEY_A){
    if(specialmode != true){
      player->Camera.yaw += P_SENSI;
    }
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
}