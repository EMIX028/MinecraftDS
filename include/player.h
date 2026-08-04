#include "mctypes.h"
#include <math.h>
#include <stdbool.h>

typedef struct{
  vec3_t position;
  float yaw;
  float pitch;
} camera_t;

typedef struct hitbox{
  float x;
  float y;
  float z;
  float w;
  float h;
  float d;
}hitbox_t;

typedef struct player{
  vec3_t Position;
  camera_t Camera;
  hitbox_t hitbox;
}player_t;

vec3_t getDir(camera_t cam);

void setPlayer(player_t *player);

void movePlayer(player_t *player, vec3_t d);

bool checkCollision(hitbox_t a, hitbox_t b);