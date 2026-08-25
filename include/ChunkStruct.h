#ifndef CHUNKSTRUCT_H
#define CHUNKSTRUCT_H

#include <stdbool.h>
#include <stdint.h>
#include "mctypes.h"
#define L_CHUNK 10 //chunk minecraft 15
#define H_CHUNK 20 // hauteur max 256

typedef struct block_s {
    uint8_t id;

    bool solid; //si on traverse ou non le block
    bool transparent; //transparence du block
    hitbox_t box;
    int hardness; //temps de destruction
    vec2_8_t texture;
    void (*draw)(const struct block_s *block);
    void (*onBreak)(int x, int y, int z);
    void (*onTick)(int x, int y, int z);

} block_t;

typedef struct chunk{
    vec2_t position;
    uint8_t blocks[L_CHUNK][H_CHUNK][L_CHUNK];
} chunk_t;

void initChunk(chunk_t *chunk, int id);

void RenderChunk(chunk_t *chunk, block_t *list, bool cull);

int floorDiv(int a, int b);

int floorMod(int a, int b);

uint8_t getBlock(chunk_t *chunk[],int size,int x,int y, int z);

void setBlock(chunk_t *chunk[],int size,int x,int y, int z, uint8_t block);

#endif