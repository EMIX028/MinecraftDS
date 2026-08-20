#ifndef BLOCKS_H
#define BLOCKS_H

#include "ChunkStruct.h"

typedef enum {
    AIR,
    DIRT,
    STONE,
    COBBLESTONE,
    LEAVES,
    BLOCK_COUNT
} Blocks;

extern block_t gBlocks[BLOCK_COUNT];

extern const hitbox_t blocks;

void InitBlocks(void);

#endif