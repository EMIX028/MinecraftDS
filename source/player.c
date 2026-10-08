#include "player.h"
#include "Blocks.h"
#include "ChunkStruct.h"
#include "mesh.h"
#include <math.h>
#include <stdint.h>

void setPlayer(player_t *player) {
  player->Position.x = divf32(F32_ONE,inttof32(2));
  player->Position.y = 0;
  player->Position.z = divf32(F32_ONE,inttof32(2));

  player->Camera.position.x = player->Position.x;
  player->Camera.position.y = player->Position.y + divf32(inttof32(81),inttof32(50)); // 81/50 = 1.62
  player->Camera.position.z = player->Position.z;

  player->Camera.yaw = 0;
  player->Camera.pitch = 0;

  player->hitbox.w = P_hitbox;
  player->hitbox.d = P_hitbox;
  player->hitbox.h = divf32(inttof32(9),inttof32(5));

  player->isfalling = false;
  player->velocityY = 0;
  player->index = DIRT;
}

void movePlayer(player_t *player, f32vec3_t d) {
  player->Position.x += d.x;
  player->Position.y += d.y;
  player->Position.z += d.z;
  player->Camera.position.x = player->Position.x;
  player->Camera.position.y = player->Position.y + divf32(inttof32(81),inttof32(50));
  player->Camera.position.z = player->Position.z;
}

void teleportPlayer(player_t *player, f32vec3_t d) {
  player->Position = d;
  player->Camera.position = d;
  player->Camera.position.y += divf32(inttof32(81),inttof32(50)); // 81/50 = 1.62
}

f32vec3_t getDir(camera_t cam) {
  f32vec3_t dir;
  dir.x = mulf32(sin_f32(cam.yaw), cos_f32(cam.pitch));
  dir.y = sin_f32(cam.pitch);
  dir.z = mulf32(- cos_f32(cam.yaw), cos_f32(cam.pitch));
  return dir;
}

bool checkCollision(f32vec3_t apos, hitbox_t a, ivec3_t bpos, hitbox_t b) {
  f32 halfW = divf32(a.w, inttof32(2));
  f32 halfD = divf32(a.d, inttof32(2));

  f32 playerMinX = apos.x - halfW;
  f32 playerMaxX = apos.x + halfW;

  f32 playerMinY = apos.y;
  f32 playerMaxY = apos.y + a.h;

  f32 playerMinZ = apos.z - halfD;
  f32 playerMaxZ = apos.z + halfD;

  f32 blockMinX = inttof32(bpos.x);
  f32 blockMaxX = inttof32(bpos.x) + b.w;

  f32 blockMinY = inttof32(bpos.y);
  f32 blockMaxY = inttof32(bpos.y) + b.h;

  f32 blockMinZ = inttof32(bpos.z);
  f32 blockMaxZ = inttof32(bpos.z) + b.d;

  return (playerMinX < blockMaxX && playerMaxX > blockMinX &&
          playerMinY < blockMaxY && playerMaxY > blockMinY &&
          playerMinZ < blockMaxZ && playerMaxZ > blockMinZ);
}



bool canMovePlayer(player_t *player, f32vec3_t movement, chunk_t chunk[], int n,
                   block_t list[], hitbox_t blocks) {
  f32vec3_t futurePosition = {.x = player->Position.x + movement.x,
                           .y = player->Position.y + movement.y,
                           .z = player->Position.z + movement.z};

  for (int i = 0; i < n; i++) {
    int chunkX = chunk[i].position.x;
    int chunkZ = chunk[i].position.z;

    for (int x = f32toint(floor_f32(futurePosition.x)) - 1;
         x <= f32toint(floor_f32(futurePosition.x)) + 1; x++) {

      for (int y = f32toint(floor_f32(futurePosition.y)) - 1;
           y <= f32toint(floor_f32(futurePosition.y)) + 2; y++) {

        for (int z = f32toint(floor_f32(futurePosition.z)) - 1;
             z <= f32toint(floor_f32(futurePosition.z)) + 1; z++) {

          if (y < 0 || y >= H_CHUNK) {
            continue;
          }
          // Coordonnées monde -> coordonnées locales du chunk
          int localX = x - chunkX * L_CHUNK;
          int localZ = z - chunkZ * L_CHUNK;

          // Le bloc n'appartient pas à ce chunk
          if (localX < 0 || localX >= L_CHUNK || localZ < 0 ||
              localZ >= L_CHUNK) {
            continue;
          }

          blockId_t blockID = chunk[i].blocks[localX][y][localZ].id;

          if (list[blockID].solid) {

            if (checkCollision(futurePosition, player->hitbox,
                               (ivec3_t){.x = x, .y = y, .z = z}, blocks)) {
              return false;
            }
          }
        }
      }
    }
  }
  return true;
}

void ATTR_FUN_INI loadPlayerMovement(player_t *player, chunk_t chunk[], int n,
                        block_t list[], hitbox_t blocks) {
  f32vec3_t m = {.x = 0, .y = 0, .z = 0};
  f32 inputX = 0;
  f32 inputZ = 0;

  player->Direction = getDir(player->Camera);

  if (keysHeld() & KEY_L) {
    specialmode = true;
  }
  if (keysUp() & KEY_L) {
    specialmode = false;
  }

  if (keysHeld() & KEY_LEFT) {
    inputX -= F32_ONE;
  }
  if (keysHeld() & KEY_RIGHT) {
    inputX += F32_ONE;
  }
  if (keysHeld() & KEY_UP) {
    inputZ += F32_ONE;
  }
  if (keysHeld() & KEY_DOWN) {
    inputZ -= F32_ONE;
  }

  f32 l = sqrtf32(mulf32(inputX, inputX) + mulf32(inputZ, inputZ));

  if (l > 0) {
    inputX = divf32(inputX, l);
    inputZ = divf32(inputZ, l);

    f32 cosyaw = cos_f32(player->Camera.yaw);
    f32 sinyaw = sin_f32(player->Camera.yaw);

    m.x = mulf32( (mulf32(inputX, cosyaw) + mulf32(inputZ, sinyaw)), P_SPEED );
    m.z = mulf32( (mulf32(inputX, sinyaw) - mulf32(inputZ, cosyaw)), P_SPEED );

    if (canMovePlayer(player, (f32vec3_t){.x = m.x, .y = 0, .z = 0}, chunk,
                      n, list, blocks)) {
      movePlayer(player, (f32vec3_t){.x = m.x, .y = 0, .z = 0});
    }

    if (canMovePlayer(player, (f32vec3_t){.x = 0, .y = 0, .z = m.z}, chunk,
                      n, list, blocks)) {
      movePlayer(player, (f32vec3_t){.x = 0, .y = 0, .z = m.z});
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





bool ATTR_FUN_INI raycastBlock(player_t *player, chunk_t chunkL[], int size,
                                       ivec3_t *outTarget, ivec3_t *outPrev,
                                       int *outHitAxis, int *outHitSign,
                                       uint8_t *outBlock) {
  f32vec3_t Raydir = getDir(player->Camera);
  f32vec3_t origin = player->Camera.position;

  ivec3_t cur = {.x = f32toint(floor_f32(origin.x)),
                 .y = f32toint(floor_f32(origin.y)),
                 .z = f32toint(floor_f32(origin.z))};

  ivec3_t target = cur;
  ivec3_t prev = cur;

  int hitAxis = -1;
  int hitSign = 0;

  ivec3_t step = {.x = (Raydir.x > 0) - (Raydir.x < 0),
                  .y = (Raydir.y > 0) - (Raydir.y < 0),
                  .z = (Raydir.z > 0) - (Raydir.z < 0)};

  f32vec3_t tDelta = {.x = (Raydir.x != 0) ? abs_f32(divf32(F32_ONE, Raydir.x)) : F32_MAX,
                      .y = (Raydir.y != 0) ? abs_f32(divf32(F32_ONE, Raydir.y)) : F32_MAX,
                      .z = (Raydir.z != 0) ? abs_f32(divf32(F32_ONE, Raydir.z)) : F32_MAX};

  f32vec3_t tMax = {.x = (Raydir.x != 0) ? 
                        mulf32( ((step.x > 0) ? 
                            (inttof32(cur.x + 1) - origin.x) : (origin.x - inttof32(cur.x))) , tDelta.x )
                        : F32_MAX,

                    .y = (Raydir.y != 0) ?
                        mulf32( ((step.y > 0) ? 
                            (inttof32(cur.y + 1) - origin.y) : (origin.y - inttof32(cur.y))) , tDelta.y )
                        : F32_MAX,

                    .z = (Raydir.z != 0) ?
                        mulf32( ((step.z > 0) ?
                            (inttof32(cur.z + 1) - origin.z) : (origin.z - inttof32(cur.z))) , tDelta.z )
                        : F32_MAX};

  bool blockTargeted = false;
  u8 b = AIR;
  f32 distance = 0;

  //la caméra est dans un bloc
  b = getBlock(chunkL, size, cur.x, cur.y, cur.z);
  if (b != AIR) {
    blockTargeted = true;
    target = cur;
  }

  while (!blockTargeted) {
    if (tMax.x < tMax.y && tMax.x < tMax.z) {
      distance = tMax.x;
      tMax.x += tDelta.x;
      cur.x += step.x;
      hitAxis = 0;
      hitSign = step.x;
    } else if (tMax.y < tMax.z) {
      distance = tMax.y;
      tMax.y += tDelta.y;
      cur.y += step.y;
      hitAxis = 1;
      hitSign = step.y;
    } else {
      distance = tMax.z;
      tMax.z += tDelta.z;
      cur.z += step.z;
      hitAxis = 2;
      hitSign = step.z;
    }

    if (distance >= P_REACH) {
      break;
    }

    b = getBlock(chunkL, size, cur.x, cur.y, cur.z);
    if (b != AIR) {
      blockTargeted = true;
      target = cur;
      // Un seul axe change : on part de target et on recule d'une case sur cet axe
      prev = target;
      switch (hitAxis) {
        case 0: prev.x -= hitSign; break;
        case 1: prev.y -= hitSign; break;
        case 2: prev.z -= hitSign; break;
      }
    }
  }

  if (!blockTargeted) {
    return false;
  }

  *outTarget = target;
  *outPrev = prev;
  *outHitAxis = hitAxis;
  *outHitSign = hitSign;
  *outBlock = b;
  return true;
}



static uint8_t computeOrientation(block_t list[], blockId_t indexB, int hitAxis, float yaw) {
  if (list[indexB].isLog) {
    // Buche : orientation dépend uniquement de la face touchée, pas du yaw
    return (hitAxis == 1) ? front_to_right : 
              (hitAxis == 0) ? front_to_left : front_to_front;
  }

  int16_t Pdeg = f32toint( mod_f32(mulf32(yaw , divf32(inttof32(180) , F32_PI)), inttof32(360)) );
  if (Pdeg > 180)
    Pdeg -= 360;
  else if (Pdeg < -180)
    Pdeg += 360;

  return (Pdeg >= -45 && Pdeg < 45) ? front_to_front :
            (Pdeg >= 45 && Pdeg < 135) ? front_to_left :
              (Pdeg >= -135 && Pdeg < -45) ? front_to_right : front_to_back;
}


static inline void notifyBlockChange(bool *majChunk, int *delay) {
  *majChunk = true;
  *delay = DELAY;
}


void ATTR_FUN_INI playerInterract(player_t *player, chunk_t chunkL[], int size,
                     blockId_t indexB, block_t list[], const bool specialmode,
                     bool *majChunk, int *delay) {
  ivec3_t target;
  ivec3_t prev;
  int hitAxis;
  int hitSign;
  u8 b;

  if (!raycastBlock(player, chunkL, size, &target, &prev, &hitAxis, &hitSign, &b)) {
    return;
  }

  drawBlockOutline(target.x, target.y, target.z);

  u32 down = keysDown();
  u32 held = keysHeld();
  u32 keys = down | held;

  bool wantsPlace = keys & KEY_R;
  bool wantsBreak = (held & KEY_L) && (keys & KEY_R);

  if (wantsPlace && !specialmode && *delay <= 0) {
    if (!checkCollision(player->Position, player->hitbox, prev, HitboxBlocks)) {
      u8 orientation = computeOrientation(list, indexB, hitAxis, player->Camera.yaw);
      setBlock(chunkL, size, prev.x, prev.y, prev.z, indexB, orientation);
      notifyBlockChange(majChunk, delay);
    }
  }

  if (wantsBreak && *delay <= 0 && b != BEDROCK) {
    setBlock(chunkL, size, target.x, target.y, target.z, AIR, front_to_front);
    notifyBlockChange(majChunk, delay);
  }
}


void setCam(player_t *player) {
  glLight(0, RGB15(31, 31, 31), floattov10(-0.5f), floattov10(-1.0f),
          floattov10(-0.3f));

  glMaterialf(GL_AMBIENT, RGB15(15, 15, 15));
  glMaterialf(GL_DIFFUSE, RGB15(31, 31, 31));
  gluLookAtf32(player->Camera.position.x, player->Camera.position.y,
            player->Camera.position.z,
            player->Camera.position.x + player->Direction.x,
            player->Camera.position.y + player->Direction.y,
            player->Camera.position.z + player->Direction.z, inttof32(0), inttof32(1), inttof32(0));
}