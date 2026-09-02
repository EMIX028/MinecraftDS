#ifndef MESH_H
#define MESH_H

#include "utils.h"
#include <stdbool.h>
#include <nds.h>

#define AMBIENT_RATIO 0.5
#define OUTLINE_SIZE 16 // Épaisseur des arêtes
#define MIN (-OUTLINE_SIZE)
#define MAX (inttov16(1) + OUTLINE_SIZE)

//initialise le rendu 3D de Quads
void startingDraw(bool cullback);

//dessine un bloc entier
void drawCube(bool cullback,vec2_t t);

//dessine sur le rendu 3D une face
void drawCubeTop(vec2_t t);
void drawCubeBottom(vec2_t t);
void drawCubeLeft(vec2_t t);
void drawCubeRight(vec2_t t);
void drawCubeFront(vec2_t t);
void drawCubeBack(vec2_t t);

//dessine un contour noir autour du bloc que l'on regarde
//si il est dans notre rayon d'action
void drawBlockOutline(int x,int y,int z);

#endif