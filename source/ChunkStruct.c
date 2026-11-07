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
  return nullptr;
}

static void blockVisibility(block_t *list, chunk_t *chunk,
                             chunk_t *leftChunk, chunk_t *rightChunk,
                             chunk_t *backChunk, chunk_t *frontChunk,
                             u8 x, u8 y, u8 z) {
  u8 faces = chunk->blocks[x][y][z].faces;

  if (list[chunk->blocks[x][y][z].id].transparent == 2) {
    chunk->blocks[x][y][z].faces = 0;
    return;
  }

  // LEFT
  if (x > 0) {
    if (list[chunk->blocks[x - 1][y][z].id].transparent != 0) {
      faces |= FACE_WEST;
    }
  } else if (leftChunk == nullptr || list[leftChunk->blocks[L_CHUNK - 1][y][z].id].transparent != 0) {
    faces |= FACE_WEST;
  }

  // RIGHT
  if (x < L_CHUNK - 1) {
    if (list[chunk->blocks[x + 1][y][z].id].transparent != 0) {
      faces |= FACE_EST;
    }
  } else if (rightChunk == nullptr || list[rightChunk->blocks[0][y][z].id].transparent != 0) {
    faces |= FACE_EST;
  }

  // BACK
  if (z > 0) {
    if (list[chunk->blocks[x][y][z - 1].id].transparent != 0) {
      faces |= FACE_NORTH;
    }
  } else if (backChunk == nullptr || list[backChunk->blocks[x][y][L_CHUNK - 1].id].transparent != 0) {
    faces |= FACE_NORTH;
  }

  // FRONT
  if (z < L_CHUNK - 1) {
    if (list[chunk->blocks[x][y][z + 1].id].transparent != 0) {
      faces |= FACE_SOUTH;
    }
  } else if (frontChunk == nullptr || list[frontChunk->blocks[x][y][0].id].transparent != 0) {
    faces |= FACE_SOUTH;
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
      logFaceTexAngle(block, orientation, front_to_est, front_to_south, &tex, &angle);
    } else {
      tex = block->texture[top];
      angle = 0;
    }
    drawTopFace(tex, angle);
  }

  if ((faces & FACE_BOTTOM) && y >= f32toint(player->Position.y)) {
    vec2_t tex;
    int angle;
    if (block->isLog) {
      logFaceTexAngle(block, orientation, front_to_est, front_to_south, &tex, &angle);
    } else {
      tex = block->texture[bottom];
      angle = 0;
    }
    drawBotFace(tex, angle);
  }

  if (faces & FACE_WEST) {
    vec2_t tex;
    int angle;
    if (block->isLog) {
      logFaceTexAngle(block, orientation, front_to_west, front_to_south, &tex, &angle);
    } else {
      tex = sideOrFrontTex(block, orientation, front_to_west);
      angle = 0;
    }
    drawWestFace(tex, angle);
  }

  if (faces & FACE_EST) {
    vec2_t tex;
    int angle;
    if (block->isLog) {
      logFaceTexAngle(block, orientation, front_to_west, front_to_south, &tex, &angle);
    } else {
      tex = sideOrFrontTex(block, orientation, front_to_est);
      angle = 0;
    }
    drawEstFace(tex, angle);
  }

  if (faces & FACE_SOUTH) {
    vec2_t tex;
    int angle;
    if (block->isLog) {
      logFaceTexAngle(block, orientation, front_to_south, front_to_west, &tex, &angle);
    } else {
      tex = sideOrFrontTex(block, orientation, front_to_south);
      angle = 0;
    }
    drawSouthFace(tex, angle);
  }

  if (faces & FACE_NORTH) {
    vec2_t tex;
    int angle;
    if (block->isLog) {
      logFaceTexAngle(block, orientation, front_to_south, front_to_west, &tex, &angle);
    } else {
      tex = sideOrFrontTex(block, orientation, front_to_north);
      angle = 0;
    }
    drawNorthFace(tex, angle);
  }
}

void ATTR_FUN_INI RenderChunk(chunk_t chunk[], block_t *list, bool cull, int TextureID, player_t *player){
  glPushMatrix();
  glTranslatef32(inttof32(chunk->position.x * L_CHUNK), 0,
                 inttof32(chunk->position.z * L_CHUNK));
  /*
  for (u8 x = 0 ; x < L_CHUNK ; ++x) {
    instance_t (*blockX)[L_CHUNK] = chunk->blocks[x];
    for (u8 y = 0 ; y < H_CHUNK ; ++y) {
      for (u8 z = 0 ; z < L_CHUNK ; ++z) {
        if(blockX[y][z].faces == 0 || blockX[y][z].id == AIR){
          continue;
        }
        block_t *block = &list[blockX[y][z].id];
        
        glPushMatrix();
        glTranslatef32(inttof32(x), inttof32(y), inttof32(z));

        RenderBlock(block, blockX[y][z].faces, blockX[y][z].orientation, x, y, z, player);

        glPopMatrix(1);
      }
    }
  }*/
  parcours_lin(L_CHUNK, H_CHUNK, L_CHUNK,
    instance_t (*blockX)[L_CHUNK] = chunk->blocks[x],
      NONE,
        {
          if(blockX[y][z].faces == 0 || blockX[y][z].id == AIR){
            continue;
          }
          block_t *block = &list[blockX[y][z].id];
        
          glPushMatrix();
          glTranslatef32(inttof32(x), inttof32(y), inttof32(z));

          RenderBlock(block, blockX[y][z].faces, blockX[y][z].orientation, x, y, z, player);

          glPopMatrix(1);
        });
  glPopMatrix(1);
}

int localblockXtoglobal(chunk_t chunk[],int x){
  return x + L_CHUNK*chunk->position.x;
}

blockId_t getBlock(chunk_t chunk[], int size, int x, int y, int z) {
  if (y < 0 || y >= H_CHUNK)
    return AIR;

  int chunkX = CHUNK_OF(x);
  int chunkZ = CHUNK_OF(z);

  int localX = LOCAL_OF(x);
  int localZ = LOCAL_OF(z);

  chunk_t *p = chunk;
  while(p < chunk + size){
    if (p->position.x == chunkX && p->position.z == chunkZ) {
      return p->blocks[localX][y][localZ].id;
    }
    p++;
  }

  return AIR;
}

chunk_t *setBlock(chunk_t chunk[], int size, int x, int y, int z, blockId_t block,
             u8 orientation) {
  if (y < 0 || y >= H_CHUNK){
    return nullptr;
  }

  int chunkX = CHUNK_OF(x);
  int chunkZ = CHUNK_OF(z);

  int localX = LOCAL_OF(x);
  int localZ = LOCAL_OF(z);

  chunk_t *p = chunk;
  while(p < chunk + size){
    if (p->position.x == chunkX && p->position.z == chunkZ) {
      p->blocks[localX][y][localZ].id = block;
      p->blocks[localX][y][localZ].orientation = orientation;
      p->blocks[localX][y][localZ].faces = 0;
      return p;
    }
    p++;
  }
  return nullptr;
}


struct direction { s8 dx, dy, dz; u8 onNeighbor, onSelf; };

static const struct direction NEIGHBORS[6] = {
  { -1,  0,  0, FACE_EST,    FACE_WEST   },
  {  1,  0,  0, FACE_WEST,   FACE_EST  },
  {  0,  0, -1, FACE_SOUTH,  FACE_NORTH   },
  {  0,  0,  1, FACE_NORTH,  FACE_SOUTH  },
  {  0, -1,  0, FACE_TOP,    FACE_BOTTOM },
  {  0,  1,  0, FACE_BOTTOM, FACE_TOP    },
};

static chunk_t *findChunk(chunk_t chunkL[], int size, chunk_t *chunk,
                          int *nx, int ny, int *nz){
  if(ny < 0 || ny >= H_CHUNK){
    return nullptr;
  }
  if(*nx >= 0 && *nx < L_CHUNK && *nz >= 0 && *nz < L_CHUNK){
    return chunk;
  }
  chunk_t *neighbor = getChunk(chunkL, size,
                               chunk->position.x + CHUNK_OF(*nx),
                               chunk->position.z + CHUNK_OF(*nz));
  *nx = LOCAL_OF(*nx);
  *nz = LOCAL_OF(*nz);
  return neighbor;
}

void updateVisibility(block_t list[], chunk_t chunkL[], int size,
                      chunk_t *chunk, int wx, int y, int wz, blockId_t block){
  if(y < 0 || y >= H_CHUNK){
    return;
  }
  int x = LOCAL_OF(wx);
  int z = LOCAL_OF(wz);

  bool drawing = list[block].transparent >= 1;
  bool solid = list[block].transparent != 2;

  u8 faces = 0;

  for(int i = 0; i < 6; i++){
    int nx = x + NEIGHBORS[i].dx;
    int ny = y + NEIGHBORS[i].dy;
    int nz = z + NEIGHBORS[i].dz;

    chunk_t *n = findChunk(chunkL, size, chunk, &nx, ny, &nz);
    bool visible = true;
    if(n != nullptr){
      instance_t *cell = &(n->blocks[nx][ny][nz]);
      u8 transparent = list[cell->id].transparent;

      if(transparent != 2){
        if(drawing){
          cell->faces |=  NEIGHBORS[i].onNeighbor;
        } else {
          cell->faces &= ~NEIGHBORS[i].onNeighbor;
        }
      }
      visible = transparent != 0;
    }

    if(visible && solid){
      faces |= NEIGHBORS[i].onSelf;
    }
  }

  chunk->blocks[x][y][z].faces = faces;
}