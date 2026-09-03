#include <math.h>
#include "player.h"
#include "mesh.h"
#include "Blocks.h"

void setPlayer(player_t *player){
  player->Position.x = 0.5f;
  player->Position.y = 0.0f;
  player->Position.z = 0.5f;

  player->Camera.position.x = player->Position.x;
  player->Camera.position.y = player->Position.y +1.62f;
  player->Camera.position.z = player->Position.z;

  player->Camera.yaw = 0.0f;
  player->Camera.pitch = 0.0f;

  player->hitbox.w = P_hitbox;
  player->hitbox.d = P_hitbox;
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

bool checkCollision(vec3_t apos , hitbox_t a , ivec3_t bpos , hitbox_t b){
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

bool canMovePlayer(player_t *player , vec3_t movement, chunk_t chunk[], int n, block_t list[], hitbox_t blocks){
  vec3_t futurePosition = {
    .x = player->Position.x + movement.x,
    .y = player->Position.y + movement.y,
    .z = player->Position.z + movement.z
  };

  for (int i = 0; i < n; i++){
    int chunkX = chunk[i].position.x;
    int chunkZ = chunk[i].position.z;

    for (int x = (int)floor(futurePosition.x) - 1;
          x <= (int)floor(futurePosition.x) + 1;
          x++){
            
      for (int y = (int)floor(futurePosition.y) - 1;
            y <= (int)floor(futurePosition.y) + 2;
            y++){
                
        for (int z = (int)floor(futurePosition.z) - 1;
              z <= (int)floor(futurePosition.z) + 1;
              z++){
                    
          if (y < 0 || y >= H_CHUNK){
            continue;
          }
          // Coordonnées monde -> coordonnées locales du chunk
          int localX = x - chunkX * L_CHUNK;
          int localZ = z - chunkZ * L_CHUNK;

          // Le bloc n'appartient pas à ce chunk
          if (localX < 0 || localX >= L_CHUNK ||
              localZ < 0 || localZ >= L_CHUNK){
            continue;
          }

          int blockID = chunk[i].blocks[localX][y][localZ].id;

          if (list[blockID].solid){
                        
            if (checkCollision(futurePosition,player->hitbox,(ivec3_t){
                .x = x,
                .y = y,
                .z = z
              },blocks)){
              return false;
            }
          }
        }
      }
    }
  }
  return true;
}

bool specialmode = false;


void loadPlayerMovement(player_t *player, chunk_t chunk[], int n, block_t list[], hitbox_t blocks){
  vec3_t m = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
  player->Direction = getDir(player->Camera);
  
  if(keysHeld() & KEY_L){
    specialmode = true;
  }
  if(keysUp() & KEY_L){
    specialmode = false;
  }
  if (keysHeld() & KEY_LEFT) {
    m.x = -(cosf(player->Camera.yaw) * P_SPEED);
    m.z = -(sinf(player->Camera.yaw) * P_SPEED);
    if (canMovePlayer(player,(vec3_t){.x=m.x,.y=0,.z=0},chunk,n,list,blocks)) {
      movePlayer(player, (vec3_t){.x=m.x,.y=0,.z=0});
    }
    if (canMovePlayer(player,(vec3_t){.x=0,.y=0,.z=m.z},chunk,n,list,blocks)) {
      movePlayer(player, (vec3_t){.x=0,.y=0,.z=m.z});
    }
  }
  if (keysHeld() & KEY_RIGHT) {
    m.x = cosf(player->Camera.yaw) * P_SPEED;
    m.z = sinf(player->Camera.yaw) * P_SPEED;
    if (canMovePlayer(player,(vec3_t){.x=m.x,.y=0,.z=0},chunk,n,list,blocks)) {
      movePlayer(player, (vec3_t){.x=m.x,.y=0,.z=0});
    }
    if (canMovePlayer(player,(vec3_t){.x=0,.y=0,.z=m.z},chunk,n,list,blocks)) {
      movePlayer(player, (vec3_t){.x=0,.y=0,.z=m.z});
    }
  }
  if (keysHeld() & KEY_UP) {
    m.x = sinf(player->Camera.yaw) * P_SPEED;
    m.z = -cosf(player->Camera.yaw) * P_SPEED;
    if (canMovePlayer(player,(vec3_t){.x=m.x,.y=0,.z=0},chunk,n,list,blocks)) {
      movePlayer(player, (vec3_t){.x=m.x,.y=0,.z=0});
    }
    if (canMovePlayer(player,(vec3_t){.x=0,.y=0,.z=m.z},chunk,n,list,blocks)) {
      movePlayer(player, (vec3_t){.x=0,.y=0,.z=m.z});
    }
  }
  if (keysHeld() & KEY_DOWN) {
    m.x = -(sinf(player->Camera.yaw) * P_SPEED);
    m.z = cosf(player->Camera.yaw) * P_SPEED;
    if (canMovePlayer(player,(vec3_t){.x=m.x,.y=0,.z=0},chunk,n,list,blocks)) {
      movePlayer(player, (vec3_t){.x=m.x,.y=0,.z=0});
    }
    if (canMovePlayer(player,(vec3_t){.x=0,.y=0,.z=m.z},chunk,n,list,blocks)) {
      movePlayer(player, (vec3_t){.x=0,.y=0,.z=m.z});
    }
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
    if(specialmode != true && sinf(player->Camera.pitch) < MAX_ANGLE){
      player->Camera.pitch += P_SENSI;
    }
  }
}

void playerInterract(player_t *player, chunk_t chunkL[], int size, int indexB,
                      const bool specialmode, bool *majChunk, int *delay){
  vec3_t target;
  bool blockTargeted;
  vec3_t Raydir;

  Raydir = getDir(player->Camera);
  vec3_t rayPos = player->Camera.position;

  vec3_t previous;
  uint8_t b;

  int previousValid = 0;

  for (float distance = 0.0f ; distance < P_REACH ; distance += 0.05f){
    rayPos.x = player->Camera.position.x + Raydir.x * distance;
    rayPos.y = player->Camera.position.y + Raydir.y * distance;
    rayPos.z = player->Camera.position.z + Raydir.z * distance;

    int bx = (int)floorf(rayPos.x);
    int by = (int)floorf(rayPos.y);
    int bz = (int)floorf(rayPos.z);

    if ((b = getBlock(chunkL,size,bx, by, bz)) != AIR){
      target.x = bx;
      target.y = by;
      target.z = bz;
      blockTargeted = true;
      if (previousValid && !checkCollision(player->Position, player->hitbox,
                                            (ivec3_t){.x=previous.x,
                                              .y=previous.y,
                                              .z=previous.z}, blocks)){
            
        if((keysDown() | keysHeld()) & KEY_R){
          if(specialmode != true && *delay <= 0){
            setBlock(chunkL, size, previous.x, previous.y, previous.z, indexB);
            *majChunk = true;
            *delay = DELAY;
          }
        }
      }
      if((keysHeld() & KEY_L) && ((keysDown() | keysHeld()) & KEY_R)){
        if(*delay <= 0 && b != BEDROCK){
          setBlock(chunkL, size, target.x, target.y, target.z, AIR);
          *majChunk = true;
          *delay = DELAY;
        }
      }
      break;
    }
    else{
      blockTargeted = false;
    }
    previous.x = bx;
    previous.y = by;
    previous.z = bz;
    previousValid = 1;
  } 
  if (blockTargeted) {
    drawBlockOutline(target.x, target.y, target.z);
  }
}