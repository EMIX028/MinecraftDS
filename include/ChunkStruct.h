#ifndef CHUNKSTRUCT_H
#define CHUNKSTRUCT_H

#include <stdbool.h>
#include <stdint.h>
#include "mctypes.h"
#define L_CHUNK 10 //chunk minecraft 15
#define H_CHUNK 15 // hauteur max 256

#define FACE_LEFT   (1 << 0)
#define FACE_RIGHT  (1 << 1)
#define FACE_TOP    (1 << 2)
#define FACE_BOTTOM (1 << 3)
#define FACE_FRONT  (1 << 4)
#define FACE_BACK   (1 << 5)

typedef struct block_s {
    uint8_t id;

    bool solid; //si on traverse ou non le block
    uint8_t transparent; //transparence du block uint8
    hitbox_t box;
    int hardness; //temps de destruction
    vec2_8_t texture;
    void (*draw)(const struct block_s *block);
    void (*onBreak)(int x, int y, int z);
    void (*onTick)(int x, int y, int z);

} block_t;

typedef struct instance{
    uint8_t id;
    uint8_t faces;
}instance_t;

typedef struct chunk{
    vec2_t position;
    instance_t blocks[L_CHUNK][H_CHUNK][L_CHUNK];
} chunk_t;

void initChunk(chunk_t *chunk, int id);

chunk_t *getChunk(chunk_t *chunks[], int size, int chunkX, int chunkZ);

void blockVisibility(chunk_t *chunks[], int size, block_t *list);

void RenderChunk(chunk_t *chunk, block_t *list, bool cull);

int floorDiv(int a, int b);

int floorMod(int a, int b);

uint8_t getBlock(chunk_t *chunk[],int size,int x,int y, int z);

void setBlock(chunk_t *chunk[],int size,int x,int y, int z, uint8_t block);

#endif