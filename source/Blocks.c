#include "Blocks.h"
#include "ChunkStruct.h"
#include "utils.h"

block_t DTCM_BSS gBlocks[BLOCK_COUNT];

const hitbox_t HitboxBlocks = {.w = F32_ONE, .h = F32_ONE,.d = F32_ONE};

//x -> ligne, z -> colonne
void InitBlocks(void){
    
    gBlocks[AIR] = (block_t){
        .id = AIR,
        .solid = false,
        .transparent = 2
    };

    gBlocks[STONE] = (block_t){
        .id = STONE,
        .transparent = 0,
        .solid = true,
        .texture[top].x = 0, .texture[top].z = 2,
        .texture[bottom].x = 0, .texture[bottom].z = 2,
        .texture[side].x = 0, .texture[side].z = 2,
        .texture[front].x = 0, .texture[front].z = 2
    };

    gBlocks[DIRT] = (block_t){
        .id = DIRT,
        .transparent = 0,
        .solid = true,
        .texture[top].x = 0, .texture[top].z = 0,
        .texture[bottom].x = 0, .texture[bottom].z = 0,
        .texture[side].x = 0, .texture[side].z = 0,
        .texture[front].x = 0, .texture[front].z = 0
    };

    gBlocks[GRASS] = (block_t){
        .id = GRASS,
        .transparent = 0,
        .solid = true,
        .texture[top].x = 0, .texture[top].z = 11,
        .texture[bottom].x = 0, .texture[bottom].z = 0,
        .texture[side].x = 0, .texture[side].z = 10,
        .texture[front].x = 0, .texture[front].z = 10
    };

    gBlocks[COBBLESTONE] = (block_t){
        .id = COBBLESTONE,
        .transparent = 0,
        .solid = true,
        .texture[top].x = 0, .texture[top].z = 3,
        .texture[bottom].x = 0, .texture[bottom].z = 3,
        .texture[side].x = 0, .texture[side].z = 3,
        .texture[front].x = 0, .texture[front].z = 3
    };

    gBlocks[OAK_PLANK] = (block_t){
        .id = OAK_PLANK,
        .transparent = 0,
        .solid = true,
        .texture[top].x = 0, .texture[top].z = 5,
        .texture[bottom].x = 0, .texture[bottom].z = 5,
        .texture[side].x = 0, .texture[side].z = 5,
        .texture[front].x = 0, .texture[front].z = 5
    };

    gBlocks[BEDROCK] = (block_t){
        .id = BEDROCK,
        .transparent = 0,
        .solid = true,
        .texture[top].x = 0, .texture[top].z = 1,
        .texture[bottom].x = 0, .texture[bottom].z = 1,
        .texture[side].x = 0, .texture[side].z = 1,
        .texture[front].x = 0, .texture[front].z = 1
    };

    gBlocks[SAND] = (block_t){
        .id = SAND,
        .transparent = 0,
        .solid = true,
        .texture[top].x = 0, .texture[top].z = 12,
        .texture[bottom].x = 0, .texture[bottom].z = 12,
        .texture[side].x = 0, .texture[side].z = 12,
        .texture[front].x = 0, .texture[front].z = 12
    };

    gBlocks[GOLD_ORE] = (block_t){
        .id = GOLD_ORE,
        .transparent = 0,
        .solid = true,
        .texture[top].x = 1, .texture[top].z = 6,
        .texture[bottom].x = 1, .texture[bottom].z = 6,
        .texture[side].x = 1, .texture[side].z = 6,
        .texture[front].x = 1, .texture[front].z = 6
    };

    gBlocks[IRON_ORE] = (block_t){
        .id = IRON_ORE,
        .transparent = 0,
        .solid = true,
        .texture[top].x = 1, .texture[top].z = 7,
        .texture[bottom].x = 1, .texture[bottom].z = 7,
        .texture[side].x = 1, .texture[side].z = 7,
        .texture[front].x = 1, .texture[front].z = 7
    };

    gBlocks[COAL_ORE] = (block_t){
        .id = COAL_ORE,
        .transparent = 0,
        .solid = true,
        .texture[top].x = 1, .texture[top].z = 5,
        .texture[bottom].x = 1, .texture[bottom].z = 5,
        .texture[side].x = 1, .texture[side].z = 5,
        .texture[front].x = 1, .texture[front].z = 5
    };

    gBlocks[OAK_LOG] = (block_t){
        .id = OAK_LOG,
        .transparent = 0,
        .solid = true,
        .isLog = true,
        .texture[top].x = 1, .texture[top].z = 3,
        .texture[bottom].x = 1, .texture[bottom].z = 3,
        .texture[side].x = 1, .texture[side].z = 2,
        .texture[front].x = 1, .texture[front].z = 2
    };

    gBlocks[OAK_LEAVE] = (block_t){
        .id = OAK_LEAVE,
        .transparent = 1,
        .solid = true,
        .texture[top].x = 1, .texture[top].z = 9,
        .texture[bottom].x = 1, .texture[bottom].z = 9,
        .texture[side].x = 1, .texture[side].z = 9,
        .texture[front].x = 1, .texture[front].z = 9
    };

    gBlocks[GLASS] = (block_t){
        .id = GLASS,
        .transparent = 1,
        .solid = true,
        .texture[top].x = 0, .texture[top].z = 4,
        .texture[bottom].x = 0, .texture[bottom].z = 4,
        .texture[side].x = 0, .texture[side].z = 4,
        .texture[front].x = 0, .texture[front].z = 4
    };

    gBlocks[OBSIDIAN] = (block_t){
        .id = OBSIDIAN,
        .transparent = 0,
        .solid = true,
        .texture[top].x = 1, .texture[top].z = 4,
        .texture[bottom].x = 1, .texture[bottom].z = 4,
        .texture[side].x = 1, .texture[side].z = 4,
        .texture[front].x = 1, .texture[front].z = 4
    };

    gBlocks[DIAMOND_ORE] = (block_t){
        .id = DIAMOND_ORE,
        .transparent = 0,
        .solid = true,
        .texture[top].x = 0, .texture[top].z = 6,
        .texture[bottom].x = 0, .texture[bottom].z = 6,
        .texture[side].x = 0, .texture[side].z = 6,
        .texture[front].x = 0, .texture[front].z = 6
    };

    gBlocks[CRAFTING_TABLE] = (block_t){
        .id = CRAFTING_TABLE,
        .transparent = 0,
        .solid = true,
        .texture[top].x = 0, .texture[top].z = 7,
        .texture[bottom].x = 0, .texture[bottom].z = 5,
        .texture[side].x = 0, .texture[side].z = 8,
        .texture[front].x = 0, .texture[front].z = 9
    };

    gBlocks[FURNACE] = (block_t){
        .id = FURNACE,
        .transparent = 0,
        .solid = true,
        .texture[top].x = 1, .texture[top].z = 1,
        .texture[bottom].x = 1, .texture[bottom].z = 1,
        .texture[side].x = 1, .texture[side].z = 0,
        .texture[front].x = 0, .texture[front].z = 13
    };

    gBlocks[REDSTONE_ORE] = (block_t){
        .id = REDSTONE_ORE,
        .transparent = 0,
        .solid = true,
        .texture[top].x = 1, .texture[top].z = 8,
        .texture[bottom].x = 1, .texture[bottom].z = 8,
        .texture[side].x = 1, .texture[side].z = 8,
        .texture[front].x = 1, .texture[front].z = 8
    };
}

const char *getBlockName(uint8_t block){
    switch (block) {
        case AIR:   return "Air";
        case STONE: return "Stone";
        case DIRT:  return "Dirt";
        case GRASS: return "Grass block";
        case COBBLESTONE: return "Cobblestone";
        case OAK_PLANK: return "Oak Plank";
        case BEDROCK: return "Bedrock";
        case SAND: return "Sand";
        case GOLD_ORE: return "Gold Ore";
        case IRON_ORE: return "Iron Ore";
        case COAL_ORE: return "Coal Ore";
        case OAK_LOG: return "Oak Log";
        case OAK_LEAVE: return "Oak Leave";
        case GLASS: return "Glass";
        case OBSIDIAN: return "Obsidian";
        case DIAMOND_ORE: return "Diamond Ore";
        case CRAFTING_TABLE: return "Crafting table";
        case FURNACE: return "Furnace";
        case REDSTONE_ORE: return "Redstone Ore";
        default:          return "UNKNOWN";
    }
}