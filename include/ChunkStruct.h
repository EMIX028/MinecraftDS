#ifndef CHUNKSTRUCT_H
#define CHUNKSTRUCT_H

#include <stdbool.h>
#include "mctypes.h"
#define L_CHUNK 15

typedef struct{
  int id;
  vec3_t position;
  void (*draw)(bool);
} block_t;

void setBlock(block_t *block, bool cullback);

typedef struct chunk{
    vec3_t position;
    block_t chunk[L_CHUNK][L_CHUNK][L_CHUNK];
} chunk_t;

void initChunk(chunk_t *chunk);

#endif