#ifndef CHUNKSTRUCT_H
#define CHUNKSTRUCT_H

#include <stdbool.h>
#include <stdint.h>
#include "PlayerStruct.h"
#include "utils.h"
#define L_CHUNK 15 //chunk minecraft 15
#define H_CHUNK 22 // hauteur max 256

//macro constante qui gère l'affichage d'un bloc sur un octet
// 1 bit par face, soit 6 bits d'utilisé sur 8
#define FACE_LEFT   (1 << 0)
#define FACE_RIGHT  (1 << 1)
#define FACE_TOP    (1 << 2)
#define FACE_BOTTOM (1 << 3)
#define FACE_FRONT  (1 << 4)
#define FACE_BACK   (1 << 5)

#define front_to_front 0
#define top_to_Z 0
#define front_to_left 1
#define top_to_X 1
#define front_to_back 2
#define top_to_Y 2
#define front_to_right 3

#define ORIENTATION_MASK (3 << 6)

#define SET_ORIENTATION(data, orientation) \
    ((data) = ((data) & 0x3F) | ((orientation) << 6))
#define GET_ORIENTATION(data) (((data) >> 6) & 0x03)
    

typedef enum{
    top,
    bottom,
    side,
    front
}faces;

/*structure d'un type de bloc avec son ID
solid qui est un booléen si on peut traverser ou non le bloc
transparent qui sert de valeur de 0 à 2 de transparence
0 : opaque, 1 : bloc contenant de la transparence, 2 : totalement transparent
texture est la coordonné de la texture dans l'atlas
*/
typedef struct block_s {
    uint8_t id;

    bool solid;
    bool isLog;
    uint8_t transparent;
    //int hardness; //temps de destruction
    vec2_t texture[4];
    //void (*draw)(const struct block_s *block);
    //void (*onBreak)(int x, int y, int z);
    //void (*onTick)(int x, int y, int z);
} block_t;

//structure présente dans les tableaux de chunk
// 1 octet pour l'id, 1 octet faces pour les faces à afficher ou non
typedef struct instance{
    uint8_t id;
    uint8_t faces;
    //dans le futur ajouté luminosité des blocs
}instance_t;

//chunk est un regroupement de bloc avec
//sa position dans le monde
//et les blocs qui le compose
typedef struct chunk{
    vec2_t position;
    instance_t blocks[L_CHUNK][H_CHUNK][L_CHUNK];
} chunk_t;

//initialise tous les blocs du chunk avec une id
void initChunk(chunk_t chunk[], int id);

//sert à obtenir le pointeur d'un chunk
//dans une liste à partir de ses coordonnées
chunk_t *getChunk(chunk_t chunks[], int size, int chunkX, int chunkZ);

//caluls les faces visibles ou non dans une liste de chunk
void blockVisibility(chunk_t chunks[], int size, block_t *list);

// dessine dans le rendu 3d un chunk
void RenderChunk(chunk_t chunk[], block_t *list, bool cull, player_t *player);

//renvoie l'id d'un bloc dans une liste de chunk
// avec sa position global
uint8_t getBlock(chunk_t chunk[],int size,int x,int y, int z);

//remplace un bloc dans une liste de chunk avec sa position global
void setBlock(chunk_t chunk[],int size,int x,int y, int z, uint8_t block, uint8_t orientation);

#endif