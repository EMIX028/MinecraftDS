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
              drawCubeRight(false,list[chunk->blocks[x][y][z]].color);
            }
            else if(list[chunk->blocks[x-1][y][z]].transparent == true){
              drawCubeLeft(false,list[chunk->blocks[x][y][z]].color);
            }
          }
          else{
            (x == 0 ? drawCubeLeft(false,list[chunk->blocks[x][y][z]].color) :
                      drawCubeRight(false,list[chunk->blocks[x][y][z]].color));
          }
          if(z != L_CHUNK - 1 && z != 0){
            if(list[chunk->blocks[x][y][z+1]].transparent == true){
              drawCubeFront(false,list[chunk->blocks[x][y][z]].color);
            }
            else if(list[chunk->blocks[x][y][z-1]].transparent == true){
              drawCubeBack(false,list[chunk->blocks[x][y][z]].color);
            }
          }
          else{
            (z == 0 ? drawCubeBack(false,list[chunk->blocks[x][y][z]].color) :
                      drawCubeFront(false,list[chunk->blocks[x][y][z]].color));
          }
          if(y != H_CHUNK - 1 && y != 0){
            if(list[chunk->blocks[x][y+1][z]].transparent == true){
              drawCubeTop(false,list[chunk->blocks[x][y][z]].color);
            }
            else if(list[chunk->blocks[x][y-1][z]].transparent == true){
              drawCubeBottom(false,list[chunk->blocks[x][y][z]].color);
            }
          }
          else{
            (y == 0 ? drawCubeBottom(false,list[chunk->blocks[x][y][z]].color) :
                      drawCubeTop(false,list[chunk->blocks[x][y][z]].color));
          }
            //drawCube(false,list[chunk->blocks[x][y][z]].color);
          glPopMatrix(1);
        }
      }
    }
  }
}