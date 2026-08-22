#include "Blocks.h"
#include <stdbool.h>

block_t gBlocks[BLOCK_COUNT];

const hitbox_t blocks = {.w = 1, .h = 1,.d = 1};


void InitBlocks(void){
    
    gBlocks[AIR] = (block_t){
        .id = AIR,
        .solid = false,
        .transparent = true
    };

    gBlocks[DIRT] = (block_t){
        .id = DIRT,
        .transparent = false,
        .solid = true,
        .texture.x = 0, .texture.y = 1
    };

    gBlocks[STONE] = (block_t){
        .id = STONE,
        .transparent = false,
        .solid = true,
        .texture.x = 1, .texture.y = 0
    };

    gBlocks[COBBLESTONE] = (block_t){
        .id = COBBLESTONE,
        .transparent = false,
        .solid = true,
        .texture.x = 1, .texture.y = 1
    };
    gBlocks[LEAVES] = (block_t){
        .id = LEAVES,
        .transparent = false,
        .solid = true,
        .texture.x = 0, .texture.y = 2
    };
}