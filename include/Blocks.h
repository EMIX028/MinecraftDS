#ifndef BLOCKS_H
#define BLOCKS_H

#include "ChunkStruct.h"

typedef enum {
    AIR,
    DIRT,
    GRASS,
    BLOCK_COUNT
} Blocks;

extern block_t gBlocks[BLOCK_COUNT];

void InitBlocks(void);

#endif