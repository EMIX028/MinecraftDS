//define this because i have some library issues
#ifndef KEY_X
    #define KEY_X (1U << 10)
#endif

#ifndef KEY_Y
    #define KEY_Y (1U << 11)
#endif

#pragma once
#include <stdint.h>
#define SCREEN_W 256
#define SCREEN_H 192
#define MAX_ANGLE 0.995

typedef struct fvec3{
  float x;
  float y;
  float z;
} vec3_t;

typedef struct ivec3{
  float x;
  float y;
  float z;
} ivec3_t;

typedef struct vec2{
  int x;
  int z;
} vec2_t;

typedef struct rgb{
  uint8_t r;
  uint8_t g;
  uint8_t b;
} rgb_t;