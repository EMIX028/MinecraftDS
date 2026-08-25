#ifndef MESH_H
#define MESH_H

#include "mctypes.h"
#include <stdbool.h>
#include <nds.h>

#define AMBIENT_RATIO 0.5
#define OUTLINE_SIZE 16 // Épaisseur des arêtes
#define MIN (-OUTLINE_SIZE)
#define MAX (inttov16(1) + OUTLINE_SIZE)

void startingDraw(bool cullback);

void drawCube(bool cullback,vec2_8_t t);

void drawCubeTop(vec2_8_t t);
void drawCubeBottom(vec2_8_t t);
void drawCubeLeft(vec2_8_t t);
void drawCubeRight(vec2_8_t t);
void drawCubeFront(vec2_8_t t);
void drawCubeBack(vec2_8_t t);
void drawBlockOutline(int x,int y,int z);

#endif