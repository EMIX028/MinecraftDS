//define this because i have some library issues
#ifndef KEY_X
    #define KEY_X (1U << 10)
#endif

#ifndef KEY_Y
    #define KEY_Y (1U << 11)
#endif

#define SCREEN_W 256
#define SCREEN_H 192
#define MAX_ANGLE 0.99


typedef struct{
  float x;
  float y;
  float z;
} vec3;

typedef struct{
  vec3 position;
  float yaw;
  float pitch;
} camera_t;

vec3 getDir(camera_t cam);