#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#define SCREEN_W 256
#define SCREEN_H 192

#define DEBUG_MODE 0

#define ATTR_FUN_INI __attribute__((section(".itcm")))

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

//type qui permet de définir tout ce qui est relatif aux id d'un bloc
typedef uint8_t blockId_t;

//Alias de plusieurs ID de bloc
typedef enum {
    AIR,
    DIRT,
    GRASS,
    SAND,
    STONE,
    COBBLESTONE,
    BEDROCK,
    GLASS,
    OAK_PLANK,
    OAK_LOG,
    OAK_LEAVE,
    OBSIDIAN,
    COAL_ORE,
    IRON_ORE,
    GOLD_ORE,
    REDSTONE_ORE,
    DIAMOND_ORE,
    CRAFTING_TABLE,
    FURNACE,
    BLOCK_COUNT
} Blocks;

typedef enum{
  RUNNING,
  PAUSED,
}GAMESTATE;

//renvoie le quotient d'une division pour un entier <0 ou >0
int floorDiv(int a, int b);

//renvoie le reste d'une division pour un entier <0 ou >0
int floorMod(int a, int b);

#endif