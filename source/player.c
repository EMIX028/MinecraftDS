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

bool specialmode = false;

void loadPlayerMovement(player_t *player, chunk_t chunk[], int n,
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

// Cette fonction à été modifié par claude /!\.
void playerInterract(player_t *player, chunk_t chunkL[], int size,
                     blockId_t indexB, block_t list[], const bool specialmode,
                     bool *majChunk, int *delay) {
  vec3_t Raydir = getDir(player->Camera);
  vec3_t origin = player->Camera.position;

  // Voxel à la position de la caméra
  ivec3_t cur = {.x = (int)floorf(origin.x),
                  .y = (int)floorf(origin.y),
                  .z = (int)floorf(origin.z)};

  // Bloc visé (celui qu'on casse) et bloc voisin (celui où on pose, collé à la
  // face touchée)
  ivec3_t target = cur;

  ivec3_t prev = cur;

  // Axe (0=X,1=Y,2=Z) et sens de la face du bloc visé qui a été traversée par
  // le rayon
  int hitAxis = -1;
  int hitSign = 0;

  // Traversée de grille façon DDA (Amanatides & Woo) : on avance exactement
  // d'une frontière de voxel à la fois
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

  // Cas limite : la caméra elle même est déjà dans un bloc plein
  b = getBlock(chunkL, size, cur.x, cur.y, cur.z);
  if (b != AIR) {
    blockTargeted = true;
    target = cur;
  }

  while (!blockTargeted && distance < P_REACH) {
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
      // Le voisin où poser un bloc est exactement celui d'où le rayon vient
      prev.x = target.x - (hitAxis == 0 ? hitSign : 0);
      prev.y = target.y - (hitAxis == 1 ? hitSign : 0);
      prev.z = target.z - (hitAxis == 2 ? hitSign : 0);
    }
  }

  if (!blockTargeted) {
    return;
  }

  drawBlockOutline(target.x, target.y, target.z);

  // Orientation du bloc à poser
  uint8_t orientation = front_to_front;
  if (list[indexB].isLog) {
    // Buche orientée selon la face du bloc visé sur laquelle on pose
    if (hitAxis == 1)
      orientation = top_to_Y; // posée sur le dessus/dessous -> verticale
    else if (hitAxis == 0)
      orientation =
          top_to_X; // posée sur une face le long de X -> couchée le long de X
    else
      orientation = top_to_Z; // posée sur une face le long de Z (ou cas caméra
                              // dans un bloc) -> couchée le long de Z
  } else {
    int16_t Pdeg = fmodf(player->Camera.yaw * (180.0f / (float)M_PI), 360.0f);
    if (Pdeg > 180.0f)
      Pdeg -= 360.0f;
    else if (Pdeg < -180.0f)
      Pdeg += 360.0f;

    if (Pdeg >= -45 && Pdeg < 45)
      orientation = front_to_front;
    else if (Pdeg >= 45 && Pdeg < 135)
      orientation = front_to_left;
    else if (Pdeg >= -135 && Pdeg < -45)
      orientation = front_to_right;
    else
      orientation = front_to_back;
  }

  if (!checkCollision(player->Position, player->hitbox, prev, HitboxBlocks)) {
    if ((keysDown() | keysHeld()) & KEY_R) {
      if (specialmode != true && *delay <= 0) {
        setBlock(chunkL, size, prev.x, prev.y, prev.z, indexB, orientation);
        *majChunk = true;
        *delay = DELAY;
      }
    }
  }

  if ((keysHeld() & KEY_L) && ((keysDown() | keysHeld()) & KEY_R)) {
    if (*delay <= 0 && b != BEDROCK) {
      setBlock(chunkL, size, target.x, target.y, target.z, AIR, front_to_front);
      *majChunk = true;
      *delay = DELAY;
    }
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