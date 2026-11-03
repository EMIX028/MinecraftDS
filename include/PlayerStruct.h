#ifndef PLAYERSTRUCT_H
#define PLAYERSTRUCT_H

#include <stdbool.h>
#include "utils.h"

//structure camera avec sa position en vecteur 3d
//sa rotation horizontal yaw et vertical pitch
typedef struct {
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
typedef struct {
  f32vec3_t Position;
  camera_t Camera;
  f32vec3_t Direction;
  hitbox_t hitbox;
  bool isfalling;
  bool iscrouch;
  f32 velocityY;
  blockId_t index;
  unsigned int facing : 2; //utilise 2 bits (0 à 3) pour si on regarde au nord, sud, est ou ouest
}player_t;

#endif