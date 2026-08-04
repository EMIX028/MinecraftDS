#include "Blocks.h"

block_t gBlocks[BLOCK_COUNT];

void InitBlocks(void){
    
    gBlocks[AIR] = (block_t){
        .id = AIR,
        .transparent = true
    };

    gBlocks[DIRT] = (block_t){
        .id = DIRT,
        .transparent = false,
        .color.r = 10, .color.g = 10, .color.b = 10
    };

    gBlocks[GRASS] = (block_t){
        .id = GRASS,
        .transparent = false,
        .color.r = 0, .color.g = 27, .color.b = 0
    };
}