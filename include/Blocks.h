#ifndef BLOCKS_H
#define BLOCKS_H

#include "ChunkStruct.h"
#include <stdint.h>

//listes des blocs du jeu avec leur caractéristiques
extern block_t gBlocks[BLOCK_COUNT];

//hitbox d'un bloc classique 
extern const hitbox_t blocks;

//fonction d'initialisation de tous les blocs
void InitBlocks(void);

const char *getBlockName(uint8_t block);

#endif