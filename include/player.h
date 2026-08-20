#include "mctypes.h"
#include <stdbool.h>
#include "ChunkStruct.h"

#define P_SPEED 0.08
#define P_SENSI 0.06
#define P_FLYSPEED 0.25
#define P_hitbox 0.6f
#define P_REACH 4.5f

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

bool checkCollision(vec3_t apos , hitbox_t a , ivec3_t bpos , hitbox_t b);

bool canMovePlayer(player_t *player ,vec3_t movement, chunk_t *chunk[], int n, block_t list[], hitbox_t blocks);

void loadPlayerMovement(player_t *player , chunk_t *chunk[], int n, block_t list[], hitbox_t blocks);