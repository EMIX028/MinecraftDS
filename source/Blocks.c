#include "Blocks.h"
#include "mctypes.h"
#include <stdbool.h>

block_t gBlocks[BLOCK_COUNT];

const hitbox_t blocks = {.w = 1, .h = 1,.d = 1};


void InitBlocks(void){
    
    gBlocks[AIR] = (block_t){
        .id = AIR,
        .solid = false,
        .transparent = 2
    };

    gBlocks[DIRT] = (block_t){
        .id = DIRT,
        .transparent = 0,
        .solid = true,
        .texture.x = 0, .texture.y = 1
    };

    gBlocks[STONE] = (block_t){
        .id = STONE,
        .transparent = 0,
        .solid = true,
        .texture.x = 1, .texture.y = 0
    };

    gBlocks[COBBLESTONE] = (block_t){
        .id = COBBLESTONE,
        .transparent = 0,
        .solid = true,
        .texture.x = 1, .texture.y = 1
    };
    gBlocks[LEAVES] = (block_t){
        .id = LEAVES,
        .transparent = 1,
        .solid = true,
        .texture.x = 0, .texture.y = 2
    };
    gBlocks[MOSS] = (block_t){
        .id = MOSS,
        .transparent = 0,
        .solid = true,
        .texture.x = 1, .texture.y = 2
    };
    gBlocks[GLASS] = (block_t){
        .id = GLASS,
        .transparent = 1,
        .solid = true,
        .texture.x = 2, .texture.y = 0
    };
}