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
        .texture.x = 0, .texture.y = 1
    };

    gBlocks[STONE] = (block_t){
        .id = STONE,
        .transparent = false,
        .texture.x = 1, .texture.y = 0
    };

    gBlocks[COBBLESTONE] = (block_t){
        .id = COBBLESTONE,
        .transparent = false,
        .texture.x = 1, .texture.y = 1
    };
}