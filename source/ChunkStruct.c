#include <nds.h>
#include "ChunkStruct.h"
#include "mctypes.h"
#include "mesh.h"

void initChunk(chunk_t *chunk, int id){
  for(short x = 0; x < L_CHUNK; ++x){
    for(short y = 0 ; y < H_CHUNK ; ++y){
      for(short z = 0 ; z < L_CHUNK ; ++z){
        chunk->blocks[x][y][z] = id;
      }
    }
  }
}

void RenderChunk(chunk_t *chunk, block_t *list, bool cull){
  for(short x = 0 ; x < L_CHUNK ; ++x){
    for(short y = 0 ; y < H_CHUNK ; ++y){
      for(short z = 0 ; z < L_CHUNK ; ++z){
        if(list[chunk->blocks[x][y][z]].transparent == false){
          glPushMatrix();
            glTranslatef32(inttof32(x + chunk->position.x*L_CHUNK),
                            inttof32(y),
                            inttof32(z + chunk->position.z*L_CHUNK));
            startingDraw(cull);
          if(x != L_CHUNK - 1 && x != 0){
            if(list[chunk->blocks[x+1][y][z]].transparent == true){
              drawCubeRight(list[chunk->blocks[x][y][z]].texture);
            }
            if(list[chunk->blocks[x-1][y][z]].transparent == true){
              drawCubeLeft(list[chunk->blocks[x][y][z]].texture);
            }
          }
          else if(x == 0){
            drawCubeLeft(list[chunk->blocks[x][y][z]].texture);
            if(list[chunk->blocks[x+1][y][z]].transparent == true){
              drawCubeRight(list[chunk->blocks[x][y][z]].texture);
            }
          } else{
            drawCubeRight(list[chunk->blocks[x][y][z]].texture);
            if(list[chunk->blocks[x-1][y][z]].transparent == true){
              drawCubeLeft(list[chunk->blocks[x][y][z]].texture);
            }
          }

          //Front & Back faces
          if(z != L_CHUNK - 1 && z != 0){
            if(list[chunk->blocks[x][y][z+1]].transparent == true){
              drawCubeFront(list[chunk->blocks[x][y][z]].texture);
            }
            if(list[chunk->blocks[x][y][z-1]].transparent == true){
              drawCubeBack(list[chunk->blocks[x][y][z]].texture);
            }
          }
          else if(z==0){
            drawCubeBack(list[chunk->blocks[x][y][z]].texture);
            if(list[chunk->blocks[x][y][z+1]].transparent == true){
              drawCubeFront(list[chunk->blocks[x][y][z]].texture);
            }
          } else{
            drawCubeFront(list[chunk->blocks[x][y][z]].texture);
            if(list[chunk->blocks[x][y][z-1]].transparent == true){
              drawCubeBack(list[chunk->blocks[x][y][z]].texture);
            }
          }

          //Top & Bottom faces
          if(y != H_CHUNK - 1 && y != 0){
            if(list[chunk->blocks[x][y+1][z]].transparent == true){
              drawCubeTop(list[chunk->blocks[x][y][z]].texture);
            }
            if(list[chunk->blocks[x][y-1][z]].transparent == true){
              drawCubeBottom(list[chunk->blocks[x][y][z]].texture);
            }
          }
          else if(y==0){
            drawCubeBottom(list[chunk->blocks[x][y][z]].texture);
            if(list[chunk->blocks[x][y+1][z]].transparent == true){
              drawCubeTop(list[chunk->blocks[x][y][z]].texture);
            }
          }
          else{
            drawCubeTop(list[chunk->blocks[x][y][z]].texture);
            if(list[chunk->blocks[x][y-1][z]].transparent == true){
              drawCubeBottom(list[chunk->blocks[x][y][z]].texture);
            }
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
      return chunk[i]->blocks[localX][y][localZ];
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
      chunk[i]->blocks[localX][y][localZ] = block;
      return;
    }
  }
}