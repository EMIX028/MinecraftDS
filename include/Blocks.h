#ifndef BLOCKS_H
#define BLOCKS_H

#include "ChunkStruct.h"

//listes des blocs du jeu avec leur caractéristiques
extern block_t MC_Blocks_list[BLOCK_COUNT];

//hitbox d'un bloc classique 
extern const hitbox_t HitboxBlocks;

//fonction d'initialisation de tous les blocs
void InitBlocks(void);

const char *getBlockName(uint8_t block);

#endif