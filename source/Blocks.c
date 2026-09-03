#include "Blocks.h"

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
        .texture.x = 0, .texture.z = 1
    };

    gBlocks[STONE] = (block_t){
        .id = STONE,
        .transparent = 0,
        .solid = true,
        .texture.x = 1, .texture.z = 0
    };

    gBlocks[COBBLESTONE] = (block_t){
        .id = COBBLESTONE,
        .transparent = 0,
        .solid = true,
        .texture.x = 1, .texture.z = 1
    };
    gBlocks[BEDROCK] = (block_t){
        .id = BEDROCK,
        .transparent = 0,
        .solid = true,
        .texture.x = 0, .texture.z = 2
    };
    gBlocks[MOSS] = (block_t){
        .id = MOSS,
        .transparent = 0,
        .solid = true,
        .texture.x = 1, .texture.z = 2
    };
    gBlocks[GLASS] = (block_t){
        .id = GLASS,
        .transparent = 1,
        .solid = true,
        .texture.x = 2, .texture.z = 0
    };
    gBlocks[PLANK] = (block_t){
        .id = PLANK,
        .transparent = 0,
        .solid = true,
        .texture.x = 2, .texture.z = 1
    };
    gBlocks[DIAMOND] = (block_t){
        .id = DIAMOND,
        .transparent = 0,
        .solid = true,
        .texture.x = 2, .texture.z = 2
    };
}

const char *getBlockName(uint8_t block){
    switch (block) {
        case AIR:   return "Air";
        case STONE: return "Stone";
        case DIRT:  return "Dirt";
        case COBBLESTONE: return "Cobblestone";
        case BEDROCK: return "Bedrock";
        case MOSS: return "Moss";
        case GLASS: return "Glass";
        case PLANK: return "Plank";
        case DIAMOND: return "Diamond";
        default:          return "UNKNOWN";
    }
}