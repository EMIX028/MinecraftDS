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

typedef struct vec2_8{
  uint8_t x;
  uint8_t y;
} vec2_8_t;

typedef struct rgb{
  uint8_t r;
  uint8_t g;
  uint8_t b;
} rgb_t;