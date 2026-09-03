#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>
#include "ChunkStruct.h"
#include "PlayerStruct.h"

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
bool canMovePlayer(player_t *player ,vec3_t movement, chunk_t chunk[], int n, block_t list[], hitbox_t blocks);

//gère les inputs de déplacement du joueur
void loadPlayerMovement(player_t *player , chunk_t chunk[], int n, block_t list[], hitbox_t blocks);

void playerInterract(player_t *player, chunk_t chunkL[], int size, int indexB,
                      const bool specialmode, bool *majChunk, int *delay);

#endif