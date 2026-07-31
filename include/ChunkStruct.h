#ifndef CHUNKSTRUCT_H
#define CHUNKSTRUCT_H

#include <stdbool.h>
#include "mctypes.h"
#define L_CHUNK 5

typedef struct{
  int id;
  vec3_t position;
  rgb_t color;
  void (*drawFront)(bool,rgb_t);
  void (*drawBack)(bool,rgb_t);
  void (*drawTop)(bool,rgb_t);
  void (*drawBottom)(bool,rgb_t);
  void (*drawLeft)(bool,rgb_t);
  void (*drawRight)(bool,rgb_t);
  void (*drawAll)(bool,rgb_t);
} block_t;

void setBlockAll(block_t *block, bool cullback);

void setBlockFaces(block_t *block, bool cullback, char face);

typedef struct chunk{
    ivec3_t position;
    block_t chunk[L_CHUNK][L_CHUNK][L_CHUNK];
} chunk_t;

void initChunk(chunk_t *chunk, block_t *block);

void drawChunk(chunk_t *chunk, bool cullback);

#endif