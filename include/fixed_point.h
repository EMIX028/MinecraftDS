#ifndef FIXED_POINT_H
#define FIXED_POINT_H

#include <nds.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h> 

typedef int32_t f32;

// i : partie entière
// d : partie décimale
// s : signe true si <0 false sinon
typedef struct partf32 {
  int32_t i;
  int16_t d;
  bool s;
} partf32_t;

#define F32_FRAC_BITS 12

// Représentation de 1.0 en Q20.12 (4096)
#define F32_ONE (1 << F32_FRAC_BITS)
// valeur de π/2 en f32
#define F32_HALF (F32_ONE / 2)
// valeur de π en f32
#define F32_PI 12868

// limite max f32
#define F32_DEC_MAX 999755859375
#define F32_INT_MAX 524287
#define F32_MAX INT32_MAX 

// limite min f32
#define F32_INT_MIN -524288
#define F32_DEC_MIN 0
#define F32_MIN INT32_MIN

// récupère la partie entière d'un f32
#define intpart(n) (inttof32(f32toint(n)))
// récupère la partie décimale d'un f32
#define decpart(n) ((n) - intpart(n))

#define SHOW_F32 "%c%ld.%04d"


// renvoie le modulo entre n et p
f32 mod_f32(f32 n, f32 p);
// Arrondis d'un flottant Q20.12 f32
f32 round_f32(f32 n);
// fait un arrondi à l'entier inférieur
f32 floor_f32(f32 n);
// Retourne la valeur absolue d'un f32
f32 abs_f32(f32 n);

// Sépare un Q20.12 en partie entière et fraction décimale sur 4 chiffres
partf32_t f32topart(f32 n);
// recompose p en un f32 Q20.12
f32 parttof32(partf32_t p);

// Renvoie le cosinus d'un angle n exprimé en radians Q20.12
f32 cos_f32(f32 n);
// Renvoie le sinus d'un angle n exprimé en radians Q20.12
f32 sin_f32(f32 n);

#endif