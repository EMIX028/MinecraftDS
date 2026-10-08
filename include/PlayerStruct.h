#ifndef PLAYERSTRUCT_H
#define PLAYERSTRUCT_H

#include <stdbool.h>
#include "utils.h"

#define P_SPEED divf32(F32_ONE,inttof32(10)) // 0.1
#define P_SENSI divf32(inttof32(3),inttof32(50)) // 0.06
#define P_FLYSPEED divf32(F32_ONE,inttof32(4)) //0.25
#define P_hitbox divf32(inttof32(3),inttof32(5)) //0.6
#define P_REACH divf32(inttof32(9),inttof32(2)) //4.5
#define DELAY 11
#define MAX_ANGLE divf32(inttof32(7),inttof32(5)) //1.4

//structure camera avec sa position en vecteur 3d
//sa rotation horizontal yaw et vertical pitch
typedef struct{
  f32vec3_t position;
  f32 yaw;
  f32 pitch;
} camera_t;

/*Structure player pour définir un joueur
sa position en vecteur 3d, sa camera de sa structure éponyme
la direction dans dans laquelle le joueur est orienté
hitbox du joueur qui est dirigé par la macro constante P_hitbox & 1.8 de hauteur
isfalling booléen de controle
velocityY pour gérer la gravité appliqué au joueur
*/
typedef struct player{
  f32vec3_t Position;
  camera_t Camera;
  f32vec3_t Direction;
  hitbox_t hitbox;
  bool isfalling;
  f32 velocityY;
  blockId_t index;
}player_t;

#endif