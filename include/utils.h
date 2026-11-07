#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stddef.h>
#include "config.h"
#include "fixed_point.h"

//booléen utilisé si on appuie sur la touche qui gère les combinaison (KEY_L)
extern bool specialmode;

//vecteur 3d en Q20.12
typedef struct {
  f32 x;
  f32 y;
  f32 z;
} f32vec3_t;

//vecteur 3d en entier
typedef struct {
  int8_t x;
  int8_t y;
  int8_t z;
} ivec3_t;

//vecteur 2d en entier
typedef struct {
  int8_t x;
  int8_t z;
} vec2_t;

//définir une hitbox avec largeur, hauteur, profondeur
typedef struct {
  f32 w;
  f32 h;
  f32 d;
}hitbox_t;

//type qui permet de définir tout ce qui est relatif aux id d'un bloc
typedef uint8_t blockId_t;

#define NONE ((void)0)

enum GAMESTATE{
  RUNNING,
  PAUSED,
  CLOSE
};

enum {
  south,
  west,
  north,
  est
};

//renvoie le quotient d'une division pour un entier <0 ou >0
int floorDiv(int a, int b);

//renvoie le reste d'une division pour un entier <0 ou >0
int floorMod(int a, int b);


#endif