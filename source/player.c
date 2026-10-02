#include "player.h"
#include "Blocks.h"
#include "ChunkStruct.h"
#include "mesh.h"
#include <math.h>
#include <stdint.h>

void setPlayer(player_t *player) {
  player->Position.x = 0.5f;
  player->Position.y = 0.0f;
  player->Position.z = 0.5f;

  player->Camera.position.x = player->Position.x;
  player->Camera.position.y = player->Position.y + 1.62f;
  player->Camera.position.z = player->Position.z;

  player->Camera.yaw = 0.0f;
  player->Camera.pitch = 0.0f;

  player->hitbox.w = P_hitbox;
  player->hitbox.d = P_hitbox;
  player->hitbox.h = 1.8f;

  player->isfalling = false;
  player->velocityY = 0.0f;
  player->index = DIRT;
}

void movePlayer(player_t *player, vec3_t d) {
  player->Position.x += d.x;
  player->Position.y += d.y;
  player->Position.z += d.z;
  player->Camera.position.x = player->Position.x;
  player->Camera.position.y = player->Position.y + 1.62f;
  player->Camera.position.z = player->Position.z;
}

void teleportPlayer(player_t *player, vec3_t d) {
  player->Position = d;
  player->Camera.position = d;
  player->Camera.position.y += 1.62f;
}

vec3_t getDir(camera_t cam) {
  vec3_t dir;
  dir.x = sinf(cam.yaw) * cosf(cam.pitch);
  dir.y = sinf(cam.pitch);
  dir.z = -cosf(cam.yaw) * cosf(cam.pitch);
  return dir;
}

bool checkCollision(vec3_t apos, hitbox_t a, ivec3_t bpos, hitbox_t b) {
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

  return (playerMinX < blockMaxX && playerMaxX > blockMinX &&

          playerMinY < blockMaxY && playerMaxY > blockMinY &&

          playerMinZ < blockMaxZ && playerMaxZ > blockMinZ);
}

bool canMovePlayer(player_t *player, vec3_t movement, chunk_t chunk[], int n,
                   block_t list[], hitbox_t blocks) {
  vec3_t futurePosition = {.x = player->Position.x + movement.x,
                           .y = player->Position.y + movement.y,
                           .z = player->Position.z + movement.z};

  for (int i = 0; i < n; i++) {
    int chunkX = chunk[i].position.x;
    int chunkZ = chunk[i].position.z;

    for (int x = (int)floor(futurePosition.x) - 1;
         x <= (int)floor(futurePosition.x) + 1; x++) {

      for (int y = (int)floor(futurePosition.y) - 1;
           y <= (int)floor(futurePosition.y) + 2; y++) {

        for (int z = (int)floor(futurePosition.z) - 1;
             z <= (int)floor(futurePosition.z) + 1; z++) {

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
  vec3_t m = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
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

  float l = sqrtf(inputX * inputX + inputZ * inputZ);

  if (l > 0.0f) {
    inputX /= l;
    inputZ /= l;

    float cosyaw = cosf(player->Camera.yaw);
    float sinyaw = sinf(player->Camera.yaw);

    m.x = (inputX * cosyaw +
           inputZ * sinyaw) *
          P_SPEED;
    m.z = (inputX * sinyaw -
           inputZ * cosyaw) *
          P_SPEED;

    if (canMovePlayer(player, (vec3_t){.x = m.x, .y = 0.0f, .z = 0.0f}, chunk,
                      n, list, blocks)) {
      movePlayer(player, (vec3_t){.x = m.x, .y = 0.0f, .z = 0.0f});
    }

    if (canMovePlayer(player, (vec3_t){.x = 0.0f, .y = 0.0f, .z = m.z}, chunk,
                      n, list, blocks)) {
      movePlayer(player, (vec3_t){.x = 0.0f, .y = 0.0f, .z = m.z});
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
  vec3_t Raydir = getDir(player->Camera);
  vec3_t origin = player->Camera.position;

  ivec3_t cur = {.x = (int)floorf(origin.x),
                 .y = (int)floorf(origin.y),
                 .z = (int)floorf(origin.z)};

  ivec3_t target = cur;
  ivec3_t prev = cur;

  int hitAxis = -1;
  int hitSign = 0;

  ivec3_t step = {.x = (Raydir.x > 0.0f) - (Raydir.x < 0.0f),
                  .y = (Raydir.y > 0.0f) - (Raydir.y < 0.0f),
                  .z = (Raydir.z > 0.0f) - (Raydir.z < 0.0f)};

  vec3_t tDelta = {.x = (Raydir.x != 0.0f) ? fabsf(1.0f / Raydir.x) : 1e30f,
                   .y = (Raydir.y != 0.0f) ? fabsf(1.0f / Raydir.y) : 1e30f,
                   .z = (Raydir.z != 0.0f) ? fabsf(1.0f / Raydir.z) : 1e30f};

  vec3_t tMax = {.x = (Raydir.x != 0.0f)
                    ? ((step.x > 0) ? ((float)(cur.x + 1) - origin.x)
                                    : (origin.x - (float)cur.x)) *
                          tDelta.x
                    : 1e30f,

                 .y = (Raydir.y != 0.0f)
                    ? ((step.y > 0) ? ((float)(cur.y + 1) - origin.y)
                                    : (origin.y - (float)cur.y)) *
                          tDelta.y
                    : 1e30f,

                 .z = (Raydir.z != 0.0f)
                    ? ((step.z > 0) ? ((float)(cur.z + 1) - origin.z)
                                    : (origin.z - (float)cur.z)) *
                          tDelta.z
                    : 1e30f};

  bool blockTargeted = false;
  uint8_t b = AIR;
  float distance = 0.0f;

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
    return (hitAxis == 1) ? front_to_right
         : (hitAxis == 0) ? front_to_left
         :                  front_to_front;
  }

  int16_t Pdeg = (int16_t)fmodf(yaw * (180.0f / (float)M_PI), 360.0f);
  if (Pdeg > 180.0f)
    Pdeg -= 360.0f;
  else if (Pdeg < -180.0f)
    Pdeg += 360.0f;

  return (Pdeg >= -45 && Pdeg < 45)   ? front_to_front
       : (Pdeg >= 45 && Pdeg < 135)   ? front_to_left
       : (Pdeg >= -135 && Pdeg < -45) ? front_to_right
       :                                front_to_back;
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
  uint8_t b;

  if (!raycastBlock(player, chunkL, size, &target, &prev, &hitAxis, &hitSign, &b)) {
    return;
  }

  drawBlockOutline(target.x, target.y, target.z);

  // keysDown()/keysHeld() lisent un état figé pour la frame : on les appelle
  // une seule fois au lieu de deux (ils ne changeront pas d'ici la fin de la fonction).
  u32 down = keysDown();
  u32 held = keysHeld();
  u32 keys = down | held;

  bool wantsPlace = keys & KEY_R;
  bool wantsBreak = (held & KEY_L) && (keys & KEY_R);

  if (wantsPlace && !specialmode && *delay <= 0) {
    if (!checkCollision(player->Position, player->hitbox, prev, HitboxBlocks)) {
      uint8_t orientation = computeOrientation(list, indexB, hitAxis, player->Camera.yaw);
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

  gluLookAt(player->Camera.position.x, player->Camera.position.y,
            player->Camera.position.z,
            player->Camera.position.x + player->Direction.x,
            player->Camera.position.y + player->Direction.y,
            player->Camera.position.z + player->Direction.z, 0.0f, 1.0f, 0.0f);
}