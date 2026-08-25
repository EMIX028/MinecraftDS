#ifndef BLOCKS_H
#define BLOCKS_H

#include "ChunkStruct.h"

extern block_t gBlocks[BLOCK_COUNT];

extern const hitbox_t blocks;

void InitBlocks(void);

#endif