#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <sys/_intsup.h>
#define SCREEN_W 256
#define SCREEN_H 192

#define DEBUG_MODE 1

//vecteur 3d en flottant
typedef struct fvec3{
  float x;
  float y;
  float z;
} vec3_t;

//vecteur 3d en entier
typedef struct ivec3{
  int8_t x;
  int8_t y;
  int8_t z;
} ivec3_t;

//vecteur 2d en entier
typedef struct vec2{
  int8_t x;
  int8_t z;
} vec2_t;

//définir une hitbox avec largeur, hauteur, profondeur
typedef struct hitbox{
  float w;
  float h;
  float d;
}hitbox_t;

//Alias de plusieurs ID de bloc
typedef enum {
    AIR,
    DIRT,
    STONE,
    COBBLESTONE,
    BEDROCK,
    GLASS,
    OAK_PLANK,
    DIAMOND_ORE,
    CRAFTING_TABLE,
    BLOCK_COUNT
} Blocks;

typedef enum{
  RUNNING,
  PAUSED,
}GAMESTATE;

#endif