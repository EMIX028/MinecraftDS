//define this because i have some library issues
// #ifndef KEY_X
//     #define KEY_X (1U << 10)
// #endif

// #ifndef KEY_Y
//     #define KEY_Y (1U << 11)
// #endif

#include "mctypes.h"
#include <math.h>
#include <stdbool.h>

#define P_SPEED 0.08
#define P_SENSI 0.06
#define P_FLYSPEED 0.25

typedef struct{
  vec3_t position;
  float yaw;
  float pitch;
} camera_t;

typedef struct player{
  vec3_t Position;
  camera_t Camera;
  vec3_t Direction;
  hitbox_t hitbox;
  bool isfalling;
  float velocityY;
}player_t;

vec3_t getDir(camera_t cam);

void setPlayer(player_t *player);

void movePlayer(player_t *player, vec3_t d);

// bool checkCollision(hitbox_t a, hitbox_t b);
bool checkCollisionTest(vec3_t apos,hitbox_t a,ivec3_t bpos, hitbox_t b);

void loadPlayerMovement(player_t *player, bool test);