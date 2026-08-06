#include <nds.h>
#include "ChunkStruct.h"
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

void RenderChunk(chunk_t *chunk, block_t *list){
  for(short x = 0 ; x < L_CHUNK ; ++x){
    for(short y = 0 ; y < H_CHUNK ; ++y){
      for(short z = 0 ; z < L_CHUNK ; ++z){
        if(list[chunk->blocks[x][y][z]].transparent == false){
          glPushMatrix();
            glTranslatef32(inttof32(x + chunk->position.x*L_CHUNK),
                            inttof32(y),
                            inttof32(z + chunk->position.z*L_CHUNK));
          if(x != L_CHUNK - 1 && x != 0){
            if(list[chunk->blocks[x+1][y][z]].transparent == true){
              drawCubeRight(false);
            }
            if(list[chunk->blocks[x-1][y][z]].transparent == true){
              drawCubeLeft(false);
            }
          }
          else if(x == 0){
            drawCubeLeft(false);
            if(list[chunk->blocks[x+1][y][z]].transparent == true){
              drawCubeRight(false);
            }
          } else{
            drawCubeRight(false);
            if(list[chunk->blocks[x-1][y][z]].transparent == true){
              drawCubeLeft(false);
            }
          }

          //Front & Back faces
          if(z != L_CHUNK - 1 && z != 0){
            if(list[chunk->blocks[x][y][z+1]].transparent == true){
              drawCubeFront(false);
            }
            if(list[chunk->blocks[x][y][z-1]].transparent == true){
              drawCubeBack(false);
            }
          }
          else if(z==0){
            drawCubeBack(false);
            if(list[chunk->blocks[x][y][z+1]].transparent == true){
              drawCubeFront(false);
            }
          } else{
            drawCubeFront(false);
            if(list[chunk->blocks[x][y][z-1]].transparent == true){
              drawCubeBack(false);
            }
          }

          //Top & Bottom faces
          if(y != H_CHUNK - 1 && y != 0){
            if(list[chunk->blocks[x][y+1][z]].transparent == true){
              drawCubeTop(false);
            }
            if(list[chunk->blocks[x][y-1][z]].transparent == true){
              drawCubeBottom(false);
            }
          }
          else if(y==0){
            drawCubeBottom(false);
            if(list[chunk->blocks[x][y+1][z]].transparent == true){
              drawCubeTop(false);
            }
          }
          else{
            drawCubeTop(false);
            if(list[chunk->blocks[x][y-1][z]].transparent == true){
              drawCubeBottom(false);
            }
          }
          glPopMatrix(1);
        }
      }
    }
  }
}