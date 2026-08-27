#include "mctypes.h"
#include <stdbool.h>
#include "ChunkStruct.h"

#define P_SPEED 0.08
#define P_SENSI 0.06
#define P_FLYSPEED 0.25
#define P_hitbox 0.6f
#define P_REACH 4.5f

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

//booléen utilisé si on appuie sur la touche qui gère les combinaison (KEY_L)
extern bool specialmode;

//donne la direction du joueur a partir de l'angle de la caméra
vec3_t getDir(camera_t cam);

//Initialise les informations du joueur
void setPlayer(player_t *player);

//déplace le joueur en addition sa position actuel avec un vecteur 3D
void movePlayer(player_t *player, vec3_t d);

//calcul la collision entre deux objet A et B avec leur hitbox
// utilise la méthode AABB (Axis Aligned Bounded Box)
bool checkCollision(vec3_t apos , hitbox_t a , ivec3_t bpos , hitbox_t b);

//vérifie si le mouvement du joueur est possible avant de l'exécuter
bool canMovePlayer(player_t *player ,vec3_t movement, chunk_t *chunk[], int n, block_t list[], hitbox_t blocks);

//gère les inputs de déplacement du joueur
void loadPlayerMovement(player_t *player , chunk_t *chunk[], int n, block_t list[], hitbox_t blocks);