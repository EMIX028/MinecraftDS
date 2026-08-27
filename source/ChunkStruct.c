#include <nds.h>
#include "ChunkStruct.h"
#include "mctypes.h"
#include "mesh.h"

void initChunk(chunk_t *chunk, int id){
  for(short x = 0; x < L_CHUNK; ++x){
    for(short y = 0 ; y < H_CHUNK ; ++y){
      for(short z = 0 ; z < L_CHUNK ; ++z){
        chunk->blocks[x][y][z].id = id;
      }
    }
  }
}

chunk_t *getChunk(chunk_t *chunks[], int size, int chunkX, int chunkZ){
  for (int i = 0; i < size; ++i){
    if (chunks[i]->position.x == chunkX && chunks[i]->position.z == chunkZ){
      return chunks[i];
    }
  }
  return NULL;
}


void blockVisibility(chunk_t *chunks[], int size, block_t *list){
  for (int i = 0; i < size; ++i){
    chunk_t *chunk = chunks[i];
    for (short x = 0; x < L_CHUNK; ++x){
      for (short y = 0; y < H_CHUNK; ++y){
        for (short z = 0; z < L_CHUNK; ++z){
          chunk->blocks[x][y][z].faces = 0;
          // LEFT
          if (x > 0){
            uint8_t neighborId = chunk->blocks[x - 1][y][z].id;
            if (list[neighborId].transparent != 0){
              chunk->blocks[x][y][z].faces |= FACE_LEFT;
            }
          }
          else{
            chunk_t *neighbor = getChunk(chunks, size, chunk->position.x - 1, chunk->position.z);
            if (neighbor == NULL || list[neighbor->blocks[L_CHUNK - 1][y][z].id].transparent != 0){
              chunk->blocks[x][y][z].faces |= FACE_LEFT;
            }
          }
          // RIGHT
          if (x < L_CHUNK - 1){
            uint8_t neighborId = chunk->blocks[x + 1][y][z].id;
            if (list[neighborId].transparent != 0){
              chunk->blocks[x][y][z].faces |= FACE_RIGHT;
            }
          }
          else{
            chunk_t *neighbor = getChunk(chunks, size, chunk->position.x + 1, chunk->position.z);
            if (neighbor == NULL || list[neighbor->blocks[0][y][z].id].transparent != 0){
              chunk->blocks[x][y][z].faces |= FACE_RIGHT;
            }
          }
          // BACK
          if (z > 0){
            uint8_t neighborId = chunk->blocks[x][y][z - 1].id;
            if (list[neighborId].transparent != 0){
              chunk->blocks[x][y][z].faces |= FACE_BACK;
            }
          }
          else{
            chunk_t *neighbor = getChunk(chunks, size, chunk->position.x, chunk->position.z - 1);
            if (neighbor == NULL || list[neighbor->blocks[x][y][L_CHUNK - 1].id].transparent != 0){
              chunk->blocks[x][y][z].faces |= FACE_BACK;
            }
          }
          // FRONT
          if (z < L_CHUNK - 1){
            uint8_t neighborId = chunk->blocks[x][y][z + 1].id;
            if (list[neighborId].transparent != 0){
              chunk->blocks[x][y][z].faces |= FACE_FRONT;
            }
          }
          else{
            chunk_t *neighbor = getChunk(chunks, size, chunk->position.x, chunk->position.z + 1);
            if (neighbor == NULL || list[neighbor->blocks[x][y][0].id].transparent != 0){
              chunk->blocks[x][y][z].faces |= FACE_FRONT;
            }
          }
          // BOTTOM
          if (y == 0){
            chunk->blocks[x][y][z].faces |= FACE_BOTTOM;
          }
          else{
            uint8_t neighborId = chunk->blocks[x][y - 1][z].id;
            if (list[neighborId].transparent != 0){
              chunk->blocks[x][y][z].faces |= FACE_BOTTOM;
            }
          }
          // TOP
          if (y == H_CHUNK - 1){
            chunk->blocks[x][y][z].faces |= FACE_TOP;
          }
          else{
            uint8_t neighborId = chunk->blocks[x][y + 1][z].id;
            if (list[neighborId].transparent != 0){
              chunk->blocks[x][y][z].faces |= FACE_TOP;
            }
          }
        }
      }
    }
  }
}

void RenderChunk(chunk_t *chunk, block_t *list, bool cull){
  for(short x = 0 ; x < L_CHUNK ; ++x){
    for(short y = 0 ; y < H_CHUNK ; ++y){
      for(short z = 0 ; z < L_CHUNK ; ++z){
        if(list[chunk->blocks[x][y][z].id].transparent < 2){
          glPushMatrix();
            glTranslatef32(inttof32(x + chunk->position.x*L_CHUNK),
                            inttof32(y),
                            inttof32(z + chunk->position.z*L_CHUNK));
            startingDraw(cull);
          if(chunk->blocks[x][y][z].faces & FACE_TOP){
            drawCubeTop(list[chunk->blocks[x][y][z].id].texture);
          }
          if(chunk->blocks[x][y][z].faces & FACE_BOTTOM){
            drawCubeBottom(list[chunk->blocks[x][y][z].id].texture);
          }
          if(chunk->blocks[x][y][z].faces & FACE_LEFT){
            drawCubeLeft(list[chunk->blocks[x][y][z].id].texture);
          }
          if(chunk->blocks[x][y][z].faces & FACE_RIGHT){
            drawCubeRight(list[chunk->blocks[x][y][z].id].texture);
          }
          if(chunk->blocks[x][y][z].faces & FACE_FRONT){
            drawCubeFront(list[chunk->blocks[x][y][z].id].texture);
          }
          if(chunk->blocks[x][y][z].faces & FACE_BACK){
            drawCubeBack(list[chunk->blocks[x][y][z].id].texture);
          }
          glEnd();
          glPopMatrix(1);
        }
      }
    }
  }
}


int floorDiv(int a, int b){
  int q = a / b;
  int r = a % b;
  if (r != 0 && a < 0) {
    q--;
  }
  return q;
}

int floorMod(int a, int b){
  int r = a % b;
  if (r < 0) {
    r += b;
  }
  return r;
}

uint8_t getBlock(chunk_t *chunk[], int size, int x, int y, int z){
  int chunkX = floorDiv(x, L_CHUNK);
  int chunkZ = floorDiv(z, L_CHUNK);

  int localX = floorMod(x, L_CHUNK);
  int localZ = floorMod(z, L_CHUNK);

  for (int i = 0; i < size; ++i) {
    if (chunk[i]->position.x == chunkX && chunk[i]->position.z == chunkZ) {
      return chunk[i]->blocks[localX][y][localZ].id;
    }
  }
  return AIR;
}

void setBlock(chunk_t *chunk[], int size,int x, int y, int z,uint8_t block){
  int chunkX = floorDiv(x, L_CHUNK);
  int chunkZ = floorDiv(z, L_CHUNK);

  int localX = floorMod(x, L_CHUNK);
  int localZ = floorMod(z, L_CHUNK);

  for (int i = 0; i < size; ++i) {
    if (chunk[i]->position.x == chunkX &&
      chunk[i]->position.z == chunkZ) {
      chunk[i]->blocks[localX][y][localZ].id = block;
      return;
    }
  }
}