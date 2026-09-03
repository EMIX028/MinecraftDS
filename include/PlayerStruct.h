#ifndef PLAYERSTRUCT_H
#define PLAYERSTRUCT_H

#include <stdbool.h>
#include "utils.h"

#define P_SPEED 0.08
#define P_SENSI 0.06
#define P_FLYSPEED 0.25
#define P_hitbox 0.6f
#define P_REACH 4.5f
#define DELAY 11

//structure camera avec sa position en vecteur 3d
//sa rotation horizontal yaw et vertical pitch
typedef struct{
  vec3_t position;
  float yaw;
  float pitch;
} camera_t;

/*Structure player pour définir un joueur
sa position en vecteur 3d, sa camera de sa structure éponyme
la direction dans dans laquelle le joueur est orienté
hitbox du joueur qui est dirigé par la macro constante P_hitbox & 1.8 de hauteur
isfalling booléen de controle
velocityY pour gérer la gravité appliqué au joueur
*/
typedef struct player{
  vec3_t Position;
  camera_t Camera;
  vec3_t Direction;
  hitbox_t hitbox;
  bool isfalling;
  float velocityY;
}player_t;

#endif