#include "Blocks.h"
#include "ChunkStruct.h"
#include "utils.h"

block_t gBlocks[BLOCK_COUNT];

const hitbox_t blocks = {.w = 1, .h = 1,.d = 1};

//x -> ligne, z -> colonne
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
        .texture[top].x = 0, .texture[top].z = 0,
        .texture[bottom].x = 0, .texture[bottom].z = 0,
        .texture[left].x = 0, .texture[left].z = 0,
        .texture[right].x = 0, .texture[right].z = 0,
        .texture[front].x = 0, .texture[front].z = 0,
        .texture[back].x = 0, .texture[back].z = 0,
    };

    gBlocks[STONE] = (block_t){
        .id = STONE,
        .transparent = 0,
        .solid = true,
        .texture[top].x = 0, .texture[top].z = 2,
        .texture[bottom].x = 0, .texture[bottom].z = 2,
        .texture[left].x = 0, .texture[left].z = 2,
        .texture[right].x = 0, .texture[right].z = 2,
        .texture[front].x = 0, .texture[front].z = 2,
        .texture[back].x = 0, .texture[back].z = 2,
    };

    gBlocks[COBBLESTONE] = (block_t){
        .id = COBBLESTONE,
        .transparent = 0,
        .solid = true,
        .texture[top].x = 0, .texture[top].z = 3,
        .texture[bottom].x = 0, .texture[bottom].z = 3,
        .texture[left].x = 0, .texture[left].z = 3,
        .texture[right].x = 0, .texture[right].z = 3,
        .texture[front].x = 0, .texture[front].z = 3,
        .texture[back].x = 0, .texture[back].z = 3,
    };
    gBlocks[BEDROCK] = (block_t){
        .id = BEDROCK,
        .transparent = 0,
        .solid = true,
        .texture[top].x = 0, .texture[top].z = 1,
        .texture[bottom].x = 0, .texture[bottom].z = 1,
        .texture[left].x = 0, .texture[left].z = 1,
        .texture[right].x = 0, .texture[right].z = 1,
        .texture[front].x = 0, .texture[front].z = 1,
        .texture[back].x = 0, .texture[back].z = 1,
    };
    gBlocks[GLASS] = (block_t){
        .id = GLASS,
        .transparent = 1,
        .solid = true,
        .texture[top].x = 0, .texture[top].z = 4,
        .texture[bottom].x = 0, .texture[bottom].z = 4,
        .texture[left].x = 0, .texture[left].z = 4,
        .texture[right].x = 0, .texture[right].z = 4,
        .texture[front].x = 0, .texture[front].z = 4,
        .texture[back].x = 0, .texture[back].z = 4,
    };
    gBlocks[OAK_PLANK] = (block_t){
        .id = OAK_PLANK,
        .transparent = 0,
        .solid = true,
        .texture[top].x = 0, .texture[top].z = 5,
        .texture[bottom].x = 0, .texture[bottom].z = 5,
        .texture[left].x = 0, .texture[left].z = 5,
        .texture[right].x = 0, .texture[right].z = 5,
        .texture[front].x = 0, .texture[front].z = 5,
        .texture[back].x = 0, .texture[back].z = 5,
    };
    gBlocks[DIAMOND_ORE] = (block_t){
        .id = DIAMOND_ORE,
        .transparent = 0,
        .solid = true,
        .texture[top].x = 0, .texture[top].z = 6,
        .texture[bottom].x = 0, .texture[bottom].z = 6,
        .texture[left].x = 0, .texture[left].z = 6,
        .texture[right].x = 0, .texture[right].z = 6,
        .texture[front].x = 0, .texture[front].z = 6,
        .texture[back].x = 0, .texture[back].z = 6,
    };
    gBlocks[CRAFTING_TABLE] = (block_t){
        .id = CRAFTING_TABLE,
        .transparent = 0,
        .solid = true,
        .texture[top].x = 0, .texture[top].z = 7,
        .texture[bottom].x = 0, .texture[bottom].z = 5,
        .texture[left].x = 0, .texture[left].z = 8,
        .texture[right].x = 0, .texture[right].z = 8,
        .texture[front].x = 0, .texture[front].z = 9,
        .texture[back].x = 0, .texture[back].z = 8,
    };
}

const char *getBlockName(uint8_t block){
    switch (block) {
        case AIR:   return "Air";
        case STONE: return "Stone";
        case DIRT:  return "Dirt";
        case COBBLESTONE: return "Cobblestone";
        case BEDROCK: return "Bedrock";
        case GLASS: return "Glass";
        case OAK_PLANK: return "Plank";
        case DIAMOND_ORE: return "Diamond";
        case CRAFTING_TABLE: return "crafting table";
        default:          return "UNKNOWN";
    }
}