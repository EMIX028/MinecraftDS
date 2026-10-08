#include "ChunkStruct.h"
#include "PlayerStruct.h"
#include "mesh.h"
#include "utils.h"
#include <stdint.h>

void initChunk(chunk_t *chunk, blockId_t id) {
  memset(chunk->blocks, id, sizeof chunk->blocks); //blockId_t fait 1 octet pour l'instant
}

chunk_t *getChunk(chunk_t chunks[], int size, int chunkX, int chunkZ) {
  for(chunk_t *p = chunks; p < chunks + size; ++p){
    if(p->position.x == chunkX && p->position.z == chunkZ){
      return p;
    }
  }
  return NULL;
}

static void blockVisibility(block_t *list, chunk_t *chunk,
                             chunk_t *leftChunk, chunk_t *rightChunk,
                             chunk_t *backChunk, chunk_t *frontChunk,
                             u8 x, u8 y, u8 z) {
  u8 faces = chunk->blocks[x][y][z].faces & ORIENTATION_MASK;

  if (list[chunk->blocks[x][y][z].id].transparent == 2) {
    chunk->blocks[x][y][z].faces = faces;
    return;
  }

  // LEFT
  if (x > 0) {
    if (list[chunk->blocks[x - 1][y][z].id].transparent != 0) {
      faces |= FACE_LEFT;
    }
  } else if (leftChunk == NULL || list[leftChunk->blocks[L_CHUNK - 1][y][z].id].transparent != 0) {
    faces |= FACE_LEFT;
  }

  // RIGHT
  if (x < L_CHUNK - 1) {
    if (list[chunk->blocks[x + 1][y][z].id].transparent != 0) {
      faces |= FACE_RIGHT;
    }
  } else if (rightChunk == NULL || list[rightChunk->blocks[0][y][z].id].transparent != 0) {
    faces |= FACE_RIGHT;
  }

  // BACK
  if (z > 0) {
    if (list[chunk->blocks[x][y][z - 1].id].transparent != 0) {
      faces |= FACE_BACK;
    }
  } else if (backChunk == NULL || list[backChunk->blocks[x][y][L_CHUNK - 1].id].transparent != 0) {
    faces |= FACE_BACK;
  }

  // FRONT
  if (z < L_CHUNK - 1) {
    if (list[chunk->blocks[x][y][z + 1].id].transparent != 0) {
      faces |= FACE_FRONT;
    }
  } else if (frontChunk == NULL || list[frontChunk->blocks[x][y][0].id].transparent != 0) {
    faces |= FACE_FRONT;
  }

  // BOTTOM
  if (y == 0) {
    faces |= FACE_BOTTOM;
  } else if (list[chunk->blocks[x][y - 1][z].id].transparent != 0) {
    faces |= FACE_BOTTOM;
  }

  // TOP
  if (y == H_CHUNK - 1) {
    faces |= FACE_TOP;
  } else if (list[chunk->blocks[x][y + 1][z].id].transparent != 0) {
    faces |= FACE_TOP;
  }
  chunk->blocks[x][y][z].faces = faces;
}

void chunkVisibility(chunk_t chunks[], int size, block_t *list) {
  for (chunk_t *p = chunks; p < chunks + size; ++p) {

    chunk_t *leftChunk  = getChunk(chunks, size, p->position.x - 1, p->position.z);
    chunk_t *rightChunk = getChunk(chunks, size, p->position.x + 1, p->position.z);
    chunk_t *backChunk  = getChunk(chunks, size, p->position.x, p->position.z - 1);
    chunk_t *frontChunk = getChunk(chunks, size, p->position.x, p->position.z + 1);

    for (u8 x = 0; x < L_CHUNK; ++x) {
      for (u8 y = 0; y < H_CHUNK; ++y) {
        for (u8 z = 0; z < L_CHUNK; ++z) {
          blockVisibility(list, p, leftChunk, rightChunk, backChunk, frontChunk, x, y, z);
        }
      }
    }
  }
}

static inline void logFaceTexAngle(block_t *block, u8 orientation,
                                    u8 matchOrientation, u8 angleOrientation,
                                    vec2_t *tex, int *angle) {
  if (orientation == matchOrientation) {
    *tex = block->texture[top];
    *angle = 0;
  } else {
    *tex = block->texture[side];
    *angle = (orientation == angleOrientation) ? 90 : 0;
  }
}

static inline vec2_t sideOrFrontTex(block_t *block, u8 orientation, u8 pivotOrientation) {
  return (orientation == pivotOrientation) ? block->texture[front] : block->texture[side];
}

static void RenderBlock(block_t *block, u8 faces, u8 orientation, int x, int y, int z, player_t *player) {
  if (faces & FACE_TOP) {
    vec2_t tex;
    int angle;
    if (block->isLog) {
      logFaceTexAngle(block, orientation, front_to_right, front_to_front, &tex, &angle);
    } else {
      tex = block->texture[top];
      angle = 0;
    }
    drawCubeTop(tex, angle);
  }

  if ((faces & FACE_BOTTOM) && y >= f32toint(player->Position.y)) {
    vec2_t tex;
    int angle;
    if (block->isLog) {
      logFaceTexAngle(block, orientation, front_to_right, front_to_front, &tex, &angle);
    } else {
      tex = block->texture[bottom];
      angle = 0;
    }
    drawCubeBottom(tex, angle);
  }

  if (faces & FACE_LEFT) {
    vec2_t tex;
    int angle;
    if (block->isLog) {
      logFaceTexAngle(block, orientation, front_to_left, front_to_front, &tex, &angle);
    } else {
      tex = sideOrFrontTex(block, orientation, front_to_left);
      angle = 0;
    }
    drawCubeLeft(tex, angle);
  }

  if (faces & FACE_RIGHT) {
    vec2_t tex;
    int angle;
    if (block->isLog) {
      logFaceTexAngle(block, orientation, front_to_left, front_to_front, &tex, &angle);
    } else {
      tex = sideOrFrontTex(block, orientation, front_to_right);
      angle = 0;
    }
    drawCubeRight(tex, angle);
  }

  if (faces & FACE_FRONT) {
    vec2_t tex;
    int angle;
    if (block->isLog) {
      logFaceTexAngle(block, orientation, front_to_front, front_to_left, &tex, &angle);
    } else {
      tex = sideOrFrontTex(block, orientation, front_to_front);
      angle = 0;
    }
    drawCubeFront(tex, angle);
  }

  if (faces & FACE_BACK) {
    vec2_t tex;
    int angle;
    if (block->isLog) {
      logFaceTexAngle(block, orientation, front_to_front, front_to_left, &tex, &angle);
    } else {
      tex = sideOrFrontTex(block, orientation, front_to_back);
      angle = 0;
    }
    drawCubeBack(tex, angle);
  }
}

void ATTR_FUN_INI RenderChunk(chunk_t chunk[], block_t *list, bool cull, int TextureID, player_t *player){
  glPushMatrix();
  glTranslatef32(inttof32(chunk->position.x * L_CHUNK), 0,
                 inttof32(chunk->position.z * L_CHUNK));
  startingDraw(cull, TextureID);
  for (u8 x = 0 ; x < L_CHUNK ; ++x) {
    instance_t (*blockX)[L_CHUNK] = chunk->blocks[x];
    for (u8 y = 0 ; y < H_CHUNK ; ++y) {
      for (u8 z = 0 ; z < L_CHUNK ; ++z) {
        block_t *block = &list[blockX[y][z].id];
        if (block->transparent >= 2) {
          continue;
        }
        u8 faces = blockX[y][z].faces;
        u8 orientation = GET_ORIENTATION(faces);
        
        glPushMatrix();
        glTranslatef32(inttof32(x), inttof32(y), inttof32(z));

        RenderBlock(block, faces, orientation, x, y, z, player);

        glPopMatrix(1);
      }
    }
  }
  glEnd();
  glPopMatrix(1);
}

int localblockXtoglobal(chunk_t chunk[],int x){
  return x + L_CHUNK*chunk->position.x;
}

blockId_t getBlock(chunk_t chunk[], int size, int x, int y, int z) {
  if (y < 0 || y >= H_CHUNK)
    return AIR;

  int chunkX = floorDiv(x, L_CHUNK);
  int chunkZ = floorDiv(z, L_CHUNK);

  int localX = floorMod(x, L_CHUNK);
  int localZ = floorMod(z, L_CHUNK);

  chunk_t *p = chunk;
  while(p < chunk + size){
    if (p->position.x == chunkX && p->position.z == chunkZ) {
      return p->blocks[localX][y][localZ].id;
    }
    p++;
  }

  return AIR;
}

int setBlock(chunk_t chunk[], int size, int x, int y, int z, blockId_t block,
             u8 orientation) {
  if (y < 0 || y >= H_CHUNK)
    return -1;

  int chunkX = floorDiv(x, L_CHUNK);
  int chunkZ = floorDiv(z, L_CHUNK);

  int localX = floorMod(x, L_CHUNK);
  int localZ = floorMod(z, L_CHUNK);

  chunk_t *p = chunk;
  while(p < chunk + size){
    if (p->position.x == chunkX && p->position.z == chunkZ) {
      p->blocks[localX][y][localZ].id = block;
      SET_ORIENTATION(p->blocks[localX][y][localZ].faces, orientation);
      return 0;
    }
    p++;
  }
  return 1;
}