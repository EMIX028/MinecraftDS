#include "mctypes.h"
#include <math.h>

typedef struct{
  vec3_t position;
  float yaw;
  float pitch;
} camera_t;

vec3_t getDir(camera_t cam);