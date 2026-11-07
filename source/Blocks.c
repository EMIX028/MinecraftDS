#include "Blocks.h"
#include "ChunkStruct.h"
#include "utils.h"

block_t DTCM_BSS MC_Blocks_list[BLOCK_COUNT];

const hitbox_t HitboxBlocks = {.w = F32_ONE, .h = F32_ONE,.d = F32_ONE};

//x -> ligne, z -> colonne
void InitBlocks(void){
    
    MC_Blocks_list[AIR] = (block_t){
        .id = AIR,
        .solid = false,
        .transparent = 2
    };

    MC_Blocks_list[STONE] = (block_t){
        .id = STONE,
        .transparent = 0,
        .solid = true,
        .texture[top].x = 0, .texture[top].z = 2,
        .texture[bottom].x = 0, .texture[bottom].z = 2,
        .texture[side].x = 0, .texture[side].z = 2,
        .texture[front].x = 0, .texture[front].z = 2
    };

    MC_Blocks_list[DIRT] = (block_t){
        .id = DIRT,
        .transparent = 0,
        .solid = true,
        .texture[top].x = 0, .texture[top].z = 0,
        .texture[bottom].x = 0, .texture[bottom].z = 0,
        .texture[side].x = 0, .texture[side].z = 0,
        .texture[front].x = 0, .texture[front].z = 0
    };

    MC_Blocks_list[GRASS] = (block_t){
        .id = GRASS,
        .transparent = 0,
        .solid = true,
        .texture[top].x = 0, .texture[top].z = 11,
        .texture[bottom].x = 0, .texture[bottom].z = 0,
        .texture[side].x = 0, .texture[side].z = 10,
        .texture[front].x = 0, .texture[front].z = 10
    };

    MC_Blocks_list[COBBLESTONE] = (block_t){
        .id = COBBLESTONE,
        .transparent = 0,
        .solid = true,
        .texture[top].x = 0, .texture[top].z = 3,
        .texture[bottom].x = 0, .texture[bottom].z = 3,
        .texture[side].x = 0, .texture[side].z = 3,
        .texture[front].x = 0, .texture[front].z = 3
    };

    MC_Blocks_list[OAK_PLANK] = (block_t){
        .id = OAK_PLANK,
        .transparent = 0,
        .solid = true,
        .texture[top].x = 0, .texture[top].z = 5,
        .texture[bottom].x = 0, .texture[bottom].z = 5,
        .texture[side].x = 0, .texture[side].z = 5,
        .texture[front].x = 0, .texture[front].z = 5
    };

    MC_Blocks_list[BEDROCK] = (block_t){
        .id = BEDROCK,
        .transparent = 0,
        .solid = true,
        .texture[top].x = 0, .texture[top].z = 1,
        .texture[bottom].x = 0, .texture[bottom].z = 1,
        .texture[side].x = 0, .texture[side].z = 1,
        .texture[front].x = 0, .texture[front].z = 1
    };

    MC_Blocks_list[SAND] = (block_t){
        .id = SAND,
        .transparent = 0,
        .solid = true,
        .texture[top].x = 0, .texture[top].z = 12,
        .texture[bottom].x = 0, .texture[bottom].z = 12,
        .texture[side].x = 0, .texture[side].z = 12,
        .texture[front].x = 0, .texture[front].z = 12
    };

    MC_Blocks_list[GOLD_ORE] = (block_t){
        .id = GOLD_ORE,
        .transparent = 0,
        .solid = true,
        .texture[top].x = 1, .texture[top].z = 6,
        .texture[bottom].x = 1, .texture[bottom].z = 6,
        .texture[side].x = 1, .texture[side].z = 6,
        .texture[front].x = 1, .texture[front].z = 6
    };

    MC_Blocks_list[IRON_ORE] = (block_t){
        .id = IRON_ORE,
        .transparent = 0,
        .solid = true,
        .texture[top].x = 1, .texture[top].z = 7,
        .texture[bottom].x = 1, .texture[bottom].z = 7,
        .texture[side].x = 1, .texture[side].z = 7,
        .texture[front].x = 1, .texture[front].z = 7
    };

    MC_Blocks_list[COAL_ORE] = (block_t){
        .id = COAL_ORE,
        .transparent = 0,
        .solid = true,
        .texture[top].x = 1, .texture[top].z = 5,
        .texture[bottom].x = 1, .texture[bottom].z = 5,
        .texture[side].x = 1, .texture[side].z = 5,
        .texture[front].x = 1, .texture[front].z = 5
    };

    MC_Blocks_list[OAK_LOG] = (block_t){
        .id = OAK_LOG,
        .transparent = 0,
        .solid = true,
        .isLog = true,
        .texture[top].x = 1, .texture[top].z = 3,
        .texture[bottom].x = 1, .texture[bottom].z = 3,
        .texture[side].x = 1, .texture[side].z = 2,
        .texture[front].x = 1, .texture[front].z = 2
    };

    MC_Blocks_list[OAK_LEAVE] = (block_t){
        .id = OAK_LEAVE,
        .transparent = 1,
        .solid = true,
        .texture[top].x = 1, .texture[top].z = 9,
        .texture[bottom].x = 1, .texture[bottom].z = 9,
        .texture[side].x = 1, .texture[side].z = 9,
        .texture[front].x = 1, .texture[front].z = 9
    };

    MC_Blocks_list[GLASS] = (block_t){
        .id = GLASS,
        .transparent = 1,
        .solid = true,
        .texture[top].x = 0, .texture[top].z = 4,
        .texture[bottom].x = 0, .texture[bottom].z = 4,
        .texture[side].x = 0, .texture[side].z = 4,
        .texture[front].x = 0, .texture[front].z = 4
    };

    MC_Blocks_list[OBSIDIAN] = (block_t){
        .id = OBSIDIAN,
        .transparent = 0,
        .solid = true,
        .texture[top].x = 1, .texture[top].z = 4,
        .texture[bottom].x = 1, .texture[bottom].z = 4,
        .texture[side].x = 1, .texture[side].z = 4,
        .texture[front].x = 1, .texture[front].z = 4
    };

    MC_Blocks_list[DIAMOND_ORE] = (block_t){
        .id = DIAMOND_ORE,
        .transparent = 0,
        .solid = true,
        .texture[top].x = 0, .texture[top].z = 6,
        .texture[bottom].x = 0, .texture[bottom].z = 6,
        .texture[side].x = 0, .texture[side].z = 6,
        .texture[front].x = 0, .texture[front].z = 6
    };

    MC_Blocks_list[CRAFTING_TABLE] = (block_t){
        .id = CRAFTING_TABLE,
        .transparent = 0,
        .solid = true,
        .texture[top].x = 0, .texture[top].z = 7,
        .texture[bottom].x = 0, .texture[bottom].z = 5,
        .texture[side].x = 0, .texture[side].z = 8,
        .texture[front].x = 0, .texture[front].z = 9
    };

    MC_Blocks_list[FURNACE] = (block_t){
        .id = FURNACE,
        .transparent = 0,
        .solid = true,
        .texture[top].x = 1, .texture[top].z = 1,
        .texture[bottom].x = 1, .texture[bottom].z = 1,
        .texture[side].x = 1, .texture[side].z = 0,
        .texture[front].x = 0, .texture[front].z = 13
    };

    MC_Blocks_list[REDSTONE_ORE] = (block_t){
        .id = REDSTONE_ORE,
        .transparent = 0,
        .solid = true,
        .texture[top].x = 1, .texture[top].z = 8,
        .texture[bottom].x = 1, .texture[bottom].z = 8,
        .texture[side].x = 1, .texture[side].z = 8,
        .texture[front].x = 1, .texture[front].z = 8
    };
}

static const char *const BLOCK_NAMES[BLOCK_COUNT] = {
#define X(id, name) [id] = name,
  BLOCK_LIST(X)
#undef X
};

const char *getBlockName(uint8_t block) {
  return block < BLOCK_COUNT ? BLOCK_NAMES[block] : "UNKNOWN";
}