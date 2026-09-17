#include "ChunkStruct.h"
#include "PlayerStruct.h"
#include "mesh.h"
#include "utils.h"
#include <stdint.h>

void initChunk(chunk_t chunk[], blockId_t id) {
  for (u8 x = 0; x < L_CHUNK; ++x) {
    for (u8 y = 0; y < H_CHUNK; ++y) {
      for (u8 z = 0; z < L_CHUNK; ++z) {
        chunk->blocks[x][y][z].id = id;
      }
    }
  }
}

chunk_t *getChunk(chunk_t chunks[], int size, int chunkX, int chunkZ) {
  for (u8 i = 0; i < size; ++i) {
    if (chunks[i].position.x == chunkX && chunks[i].position.z == chunkZ) {
      return &chunks[i];
    }
  }
  return NULL;
}

void blockVisibility(chunk_t chunks[], int size, block_t *list) {
  for (u8 i = 0; i < size; ++i) {
    chunk_t *chunk = &chunks[i];
    for (u8 x = 0; x < L_CHUNK; ++x) {
      for (u8 y = 0; y < H_CHUNK; ++y) {
        for (u8 z = 0; z < L_CHUNK; ++z) {
          chunk->blocks[x][y][z].faces &= ORIENTATION_MASK;
          // L'air n'a pas de faces à dessiner
          if (list[chunk->blocks[x][y][z].id].transparent == 2) {
            continue;
          }
          // LEFT
          if (x > 0) {
            blockId_t neighborId = chunk->blocks[x - 1][y][z].id;
            if (list[neighborId].transparent != 0) {
              chunk->blocks[x][y][z].faces |= FACE_LEFT;
            }
          } else {
            chunk_t *neighbor = getChunk(chunks, size, chunk->position.x - 1,
                                         chunk->position.z);
            if (neighbor == NULL ||
                list[neighbor->blocks[L_CHUNK - 1][y][z].id].transparent != 0) {
              chunk->blocks[x][y][z].faces |= FACE_LEFT;
            }
          }
          // RIGHT
          if (x < L_CHUNK - 1) {
            blockId_t neighborId = chunk->blocks[x + 1][y][z].id;
            if (list[neighborId].transparent != 0) {
              chunk->blocks[x][y][z].faces |= FACE_RIGHT;
            }
          } else {
            chunk_t *neighbor = getChunk(chunks, size, chunk->position.x + 1,
                                         chunk->position.z);
            if (neighbor == NULL ||
                list[neighbor->blocks[0][y][z].id].transparent != 0) {
              chunk->blocks[x][y][z].faces |= FACE_RIGHT;
            }
          }
          // BACK
          if (z > 0) {
            blockId_t neighborId = chunk->blocks[x][y][z - 1].id;
            if (list[neighborId].transparent != 0) {
              chunk->blocks[x][y][z].faces |= FACE_BACK;
            }
          } else {
            chunk_t *neighbor = getChunk(chunks, size, chunk->position.x,
                                         chunk->position.z - 1);
            if (neighbor == NULL ||
                list[neighbor->blocks[x][y][L_CHUNK - 1].id].transparent != 0) {
              chunk->blocks[x][y][z].faces |= FACE_BACK;
            }
          }
          // FRONT
          if (z < L_CHUNK - 1) {
            blockId_t neighborId = chunk->blocks[x][y][z + 1].id;
            if (list[neighborId].transparent != 0) {
              chunk->blocks[x][y][z].faces |= FACE_FRONT;
            }
          } else {
            chunk_t *neighbor = getChunk(chunks, size, chunk->position.x,
                                         chunk->position.z + 1);
            if (neighbor == NULL ||
                list[neighbor->blocks[x][y][0].id].transparent != 0) {
              chunk->blocks[x][y][z].faces |= FACE_FRONT;
            }
          }
          // BOTTOM
          if (y == 0) {
            chunk->blocks[x][y][z].faces |= FACE_BOTTOM;
          } else {
            blockId_t neighborId = chunk->blocks[x][y - 1][z].id;
            if (list[neighborId].transparent != 0) {
              chunk->blocks[x][y][z].faces |= FACE_BOTTOM;
            }
          }
          // TOP
          if (y == H_CHUNK - 1) {
            chunk->blocks[x][y][z].faces |= FACE_TOP;
          } else {
            blockId_t neighborId = chunk->blocks[x][y + 1][z].id;
            if (list[neighborId].transparent != 0) {
              chunk->blocks[x][y][z].faces |= FACE_TOP;
            }
          }
        }
      }
    }
  }
}

void ATTR_FUN_INI RenderChunk(
    chunk_t chunk[], block_t *list, bool cull,
    player_t *player) { // attribute en fix temporaire pour les performances
  glPushMatrix();
  glTranslatef32(inttof32(chunk->position.x * L_CHUNK), 0,
                 inttof32(chunk->position.z * L_CHUNK));
  startingDraw(cull);
  for (u8 x = 0; x < L_CHUNK; ++x) {
    for (u8 y = 0; y < H_CHUNK; ++y) {
      for (u8 z = 0; z < L_CHUNK; ++z) {
        block_t *block = &list[chunk->blocks[x][y][z].id];
        u8 faces = chunk->blocks[x][y][z].faces;
        u8 orientation = GET_ORIENTATION(faces);
        if (block->transparent >= 2) {
          continue;
        }
        glPushMatrix();
        glTranslatef32(inttof32(x), inttof32(y), inttof32(z));

        if (faces & FACE_TOP) {
          if (block->isLog) {
            if (orientation == top_to_Y) {
              drawCubeTop(block->texture[top], 0);
            } else {
              if (orientation == top_to_Z)
                drawCubeTop(block->texture[side], 90);
              else
                drawCubeTop(block->texture[side], 0);
            }
          } else
            drawCubeTop(block->texture[top], 0);
        }

        if ((faces & FACE_BOTTOM) && y >= player->Position.y) {
          if (block->isLog) {
            if (orientation == top_to_Y) {
              drawCubeBottom(block->texture[top], 0);
            } else {
              if (orientation == top_to_Z)
                drawCubeBottom(block->texture[side], 90);
              else
                drawCubeBottom(block->texture[side], 0);
            }
          } else
            drawCubeBottom(block->texture[bottom], 0);
        }

        if (faces & FACE_LEFT) {
          if (block->isLog) {
            if (orientation == top_to_X) {
              drawCubeLeft(block->texture[top], 0);
            } else {
              if (orientation == top_to_Z)
                drawCubeLeft(block->texture[side], 90);
              else
                drawCubeLeft(block->texture[side], 0);
            }
          } else {
            if (orientation == front_to_left) {
              drawCubeLeft(block->texture[front], 0);
            } else {
              drawCubeLeft(block->texture[side], 0);
            }
          }
        }

        if (faces & FACE_RIGHT) {
          if (block->isLog) {
            if (orientation == top_to_X) {
              drawCubeRight(block->texture[top], 0);
            } else {
              if (orientation == top_to_Z)
                drawCubeRight(block->texture[side], 90);
              else
                drawCubeRight(block->texture[side], 0);
            }
          } else {
            if (orientation == front_to_right)
              drawCubeRight(block->texture[front], 0);
            else
              drawCubeRight(block->texture[side], 0);
          }
        }

        if (faces & FACE_FRONT) {
          if (block->isLog) {
            if (orientation == top_to_Z) {
              drawCubeFront(block->texture[top], 0);
            } else {
              if (orientation == top_to_X)
                drawCubeFront(block->texture[side], 90);
              else
                drawCubeFront(block->texture[side], 0);
            }
          } else {
            if (orientation == front_to_front)
              drawCubeFront(block->texture[front], 0);
            else
              drawCubeFront(block->texture[side], 0);
          }
        }

        if (faces & FACE_BACK) {
          if (block->isLog) {
            if (orientation == top_to_Z) {
              drawCubeBack(block->texture[top], 0);
            } else {
              if (orientation == top_to_X)
                drawCubeBack(block->texture[side], 90);
              else
                drawCubeBack(block->texture[side], 0);
            }
          } else {
            if (orientation == front_to_back)
              drawCubeBack(block->texture[front], 0);
            else
              drawCubeBack(block->texture[side], 0);
          }
        }
        glPopMatrix(1);
      }
    }
  }
  glEnd();
  glPopMatrix(1);
}

blockId_t getBlock(chunk_t chunk[], int size, int x, int y, int z) {
  if (y < 0 || y >= H_CHUNK)
    return AIR;

  int chunkX = floorDiv(x, L_CHUNK);
  int chunkZ = floorDiv(z, L_CHUNK);

  int localX = floorMod(x, L_CHUNK);
  int localZ = floorMod(z, L_CHUNK);

  for (u8 i = 0; i < size; ++i) {
    if (chunk[i].position.x == chunkX && chunk[i].position.z == chunkZ) {
      return chunk[i].blocks[localX][y][localZ].id;
    }
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

  for (u8 i = 0; i < size; ++i) {
    if (chunk[i].position.x == chunkX && chunk[i].position.z == chunkZ) {
      chunk[i].blocks[localX][y][localZ].id = block;
      SET_ORIENTATION(chunk[i].blocks[localX][y][localZ].faces, orientation);
      return 0;
    }
  }
  return 1;
}
