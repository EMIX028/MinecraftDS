#include <nds.h>
#include "ChunkStruct.h"

void setBlockAll(block_t *block, bool cullback){
  glPushMatrix();
    glTranslatef32(floattof32(block->position.x),
                    floattof32(block->position.y),
                    floattof32(block->position.z));
  if(block->drawAll != NULL){
      block->drawAll(cullback,block->color);
    }
  glPopMatrix(1);
}

void setBlockFaces(block_t *block, bool cullback, char face){
  // Top : T, Bottom : B, Front : F, Back : A, Left : L, Right : R
  glPushMatrix();
    glTranslatef32(floattof32(block->position.x),
                    floattof32(block->position.y),
                    floattof32(block->position.z));
    if(face == 'T' && block->drawTop != NULL){
      block->drawTop(cullback,block->color);
    }
    else if(face == 'B' && block->drawBottom != NULL){
      block->drawBottom(cullback,block->color);
    }
    else if(face == 'F' && block->drawFront != NULL){
      block->drawFront(cullback,block->color);
    }
    else if(face == 'A' && block->drawBack != NULL){
      block->drawBack(cullback,block->color);
    }
    else if(face == 'L' && block->drawLeft != NULL){
      block->drawLeft(cullback,block->color);
    }
    else if(face == 'R' && block->drawRight != NULL){
      block->drawRight(cullback,block->color);
    }
  glPopMatrix(1);
}

void initChunk(chunk_t *chunk, block_t *block){
  for(short x = 0; x < L_CHUNK; ++x){
    for(short y = 0 ; y < L_CHUNK ; ++y){
      for(short z = 0 ; z < L_CHUNK ; ++z){
        chunk->chunk[x][y][z] = *block;
        chunk->chunk[x][y][z].position.x = x + chunk->position.x * L_CHUNK;
        chunk->chunk[x][y][z].position.y = y + chunk->position.y * L_CHUNK;
        chunk->chunk[x][y][z].position.z = z + chunk->position.z * L_CHUNK;
      }
    }
  }
}

void drawChunk(chunk_t *chunk, bool cullback){
  for(short x = 0; x < L_CHUNK; ++x){
    for(short y = 0 ; y < L_CHUNK ; ++y){
      for(short z = 0 ; z < L_CHUNK ; ++z){
        setBlockAll(&chunk->chunk[x][y][z],cullback);
      }
    }
  }
}