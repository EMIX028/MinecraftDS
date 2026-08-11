#include "player.h"
#include <nds.h>

void setPlayer(player_t *player){
  player->Position.x = 0.5f;
  player->Position.y = 0.0f;
  player->Position.z = 0.5f;

  player->Camera.position.x = player->Position.x;
  player->Camera.position.y = player->Position.y +1.5f;
  player->Camera.position.z = player->Position.z;

  player->Camera.yaw = 0.0f;
  player->Camera.pitch = 0.0f;

  player->hitbox.w = 0.8f;
  player->hitbox.d = 0.8f;
  player->hitbox.h = 1.8f;

  player->isfalling = false;
  player->velocityY = 0.0f;
}

void movePlayer(player_t *player, vec3_t d){
  player->Position.x += d.x;
  player->Position.y += d.y;
  player->Position.z += d.z;
  player->Camera.position.x = player->Position.x;
  player->Camera.position.y = player->Position.y +1.5f;
  player->Camera.position.z = player->Position.z;
}

vec3_t getDir(camera_t cam){
  vec3_t dir;
  dir.x = sinf(cam.yaw)*cosf(cam.pitch);
  dir.y = sinf(cam.pitch);
  dir.z = -cosf(cam.yaw)*cosf(cam.pitch);
  return dir;
}

// bool checkCollision(hitbox_t a, hitbox_t b){
//     return (
//       a.x < b.x + b.w &&
//       a.x + a.w > b.x &&

//       a.y < b.y + b.h &&
//       a.y + a.h > b.y &&

//       a.z < b.z + b.d &&
//       a.z + a.d > b.z
//     );
// }

bool checkCollisionTest(vec3_t apos,hitbox_t a,ivec3_t bpos,hitbox_t b){
    float playerMinX = apos.x - a.w / 2.0f;
    float playerMaxX = apos.x + a.w / 2.0f;

    float playerMinY = apos.y;
    float playerMaxY = apos.y + a.h;

    float playerMinZ = apos.z - a.d / 2.0f;
    float playerMaxZ = apos.z + a.d / 2.0f;

    float blockMinX = bpos.x;
    float blockMaxX = bpos.x + b.w;

    float blockMinY = bpos.y;
    float blockMaxY = bpos.y + b.h;

    float blockMinZ = bpos.z;
    float blockMaxZ = bpos.z + b.d;

    return (
        playerMinX < blockMaxX &&
        playerMaxX > blockMinX &&

        playerMinY < blockMaxY &&
        playerMaxY > blockMinY &&

        playerMinZ < blockMaxZ &&
        playerMaxZ > blockMinZ
    );
}

bool checkCollisionPlayerBlock(player_t player,ivec3_t bpos,hitbox_t b){
    float playerMinX = player.Position.x - player.hitbox.w / 2.0f;
    float playerMaxX = player.Position.x + player.hitbox.w / 2.0f;

    float playerMinY = player.Position.y;
    float playerMaxY = player.Position.y + player.hitbox.h;

    float playerMinZ = player.Position.z - player.hitbox.d / 2.0f;
    float playerMaxZ = player.Position.z + player.hitbox.d / 2.0f;

    float blockMinX = bpos.x;
    float blockMaxX = bpos.x + b.w;

    float blockMinY = bpos.y;
    float blockMaxY = bpos.y + b.h;

    float blockMinZ = bpos.z;
    float blockMaxZ = bpos.z + b.d;

    return (
        playerMinX < blockMaxX &&
        playerMaxX > blockMinX &&

        playerMinY < blockMaxY &&
        playerMaxY > blockMinY &&

        playerMinZ < blockMaxZ &&
        playerMaxZ > blockMinZ
    );
}

void loadPlayerMovement(player_t *player){
  player->Direction = getDir(player->Camera);
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