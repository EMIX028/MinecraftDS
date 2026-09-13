#include <math.h>
#include <stdint.h>
#include "player.h"
#include "ChunkStruct.h"
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
  player->Camera.position.y = player->Position.y +1.62f;
  player->Camera.position.z = player->Position.z;
}

void teleportPlayer(player_t *player, vec3_t d){
  player->Position = d;
  player->Camera.position = d;
  player->Camera.position.y += 1.62f;
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

          blockId_t blockID = chunk[i].blocks[localX][y][localZ].id;

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

void loadPlayerMovement(player_t *player,chunk_t chunk[],int n,block_t list[],hitbox_t blocks){
  vec3_t m = {
    .x = 0.0f,
    .y = 0.0f,
    .z = 0.0f
  };
  float inputX = 0.0f;
  float inputZ = 0.0f;

  player->Direction = getDir(player->Camera);

  if (keysHeld() & KEY_L) {
    specialmode = true;
  }
  if (keysUp() & KEY_L) {
    specialmode = false;
  }

  if (keysHeld() & KEY_LEFT) {
    inputX -= 1.0f;
  }
  if (keysHeld() & KEY_RIGHT) {
    inputX += 1.0f;
  }
  if (keysHeld() & KEY_UP) {
    inputZ += 1.0f;
  }
  if (keysHeld() & KEY_DOWN) {
    inputZ -= 1.0f;
  }

  float l = sqrtf(inputX * inputX +inputZ * inputZ);

  if (l > 0.0f) {
    inputX /= l;
    inputZ /= l;

    m.x = ( inputX * cosf(player->Camera.yaw) + inputZ * sinf(player->Camera.yaw) ) * P_SPEED;
    m.z = ( inputX * sinf(player->Camera.yaw) - inputZ * cosf(player->Camera.yaw) ) * P_SPEED;

    if (canMovePlayer(player,(vec3_t){.x = m.x,.y = 0.0f,.z = 0.0f}, chunk, n, list, blocks)){
      movePlayer(player,(vec3_t){.x = m.x,.y = 0.0f,.z = 0.0f});
    }

    if (canMovePlayer(player,(vec3_t){.x = 0.0f,.y = 0.0f,.z = m.z}, chunk, n, list, blocks)){
      movePlayer(player,(vec3_t){.x = 0.0f,.y = 0.0f,.z = m.z});
    }
  }

  if ((keysHeld() & KEY_Y) && !specialmode)
    player->Camera.yaw -= P_SENSI;

  if ((keysHeld() & KEY_A) && !specialmode)
    player->Camera.yaw += P_SENSI;

  if ((keysHeld() & KEY_B) && !specialmode && player->Camera.pitch > -MAX_ANGLE)
    player->Camera.pitch -= P_SENSI;

  if ((keysHeld() & KEY_X) && !specialmode && player->Camera.pitch < MAX_ANGLE)
    player->Camera.pitch += P_SENSI;
}

void playerInterract(player_t *player, chunk_t chunkL[], int size, blockId_t indexB,block_t list[],
                      const bool specialmode, bool *majChunk, int *delay){
  vec3_t target;
  bool blockTargeted;
  vec3_t Raydir;

  Raydir = getDir(player->Camera);
  vec3_t rayPos = player->Camera.position;

  vec3_t previous;
  uint8_t b;

  int previousValid = 0;

  int16_t Pdeg = fmodf(player->Camera.yaw * (180.0f / (float)M_PI), 360.0f);
  if (Pdeg > 180.0)
    Pdeg -= 360.0;
  else if (Pdeg < -180.0)
    Pdeg += 360.0;
  uint8_t orientation = front_to_front;
  if(list[indexB].isLog){
    if(-1.0f >= player->Camera.pitch || player->Camera.pitch >= 1.0f){
      orientation = top_to_Y;
    }
    else{
      if ((Pdeg >= 45 && Pdeg < 135) || (Pdeg >= -135 && Pdeg < -45)){
        orientation = top_to_X;
      }
      else{
        orientation = top_to_Z;
      }
    }
  }
  else{
    if (Pdeg >= -45 && Pdeg < 45)
      orientation = front_to_front;
    else if (Pdeg >= 45 && Pdeg < 135)
      orientation = front_to_left;
    else if (Pdeg >= -135 && Pdeg < -45)
      orientation = front_to_right;
    else
      orientation = front_to_back;
  }

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
                                              .z=previous.z}, HitboxBlocks)){
            
        if((keysDown() | keysHeld()) & KEY_R){
          if(specialmode != true && *delay <= 0){
            setBlock(chunkL, size, previous.x, previous.y, previous.z, indexB,orientation);
            *majChunk = true;
            *delay = DELAY;
          }
        }
      }
      if((keysHeld() & KEY_L) && ((keysDown() | keysHeld()) & KEY_R)){
        if(*delay <= 0 && b != BEDROCK){
          setBlock(chunkL, size, target.x, target.y, target.z, AIR, front_to_front);
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

void setCam(player_t *player){
  glLight(
      0,
      RGB15(31,31,31),
      floattov10(-0.5f),
      floattov10(-1.0f),
      floattov10(-0.3f)
    );

  glMaterialf(GL_AMBIENT, RGB15(15,15,15));
  glMaterialf(GL_DIFFUSE, RGB15(31,31,31));

  gluLookAt(
    player->Camera.position.x, player->Camera.position.y, player->Camera.position.z,
    player->Camera.position.x + player->Direction.x, player->Camera.position.y + player->Direction.y, player->Camera.position.z + player->Direction.z,
    0.0f, 1.0f, 0.0f
  );
}