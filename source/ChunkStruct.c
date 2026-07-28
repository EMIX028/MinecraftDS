#include <nds.h>
#include "ChunkStruct.h"

block_t air = {.id = 0,
                .draw = NULL};

void setBlock(block_t *block, bool cullback){
  glPushMatrix();
    glTranslatef32(floattof32(block->position.x),
                    floattof32(block->position.x),
                    floattof32(block->position.x));
    block->draw(cullback);
  glPopMatrix(1);
}

void initChunk(chunk_t *chunk){
  for(short int x = 0; x < 15; ++x){
    for(short int y = 0 ; y < 15 ; ++y){
      for(short int z = 0 ; z < 15 ; ++z){
        chunk->chunk[x][y][z] = air;
      }
    }
  }
}