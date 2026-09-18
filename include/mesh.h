#ifndef MESH_H
#define MESH_H

#include <nds.h>
#include <stdbool.h>
#include <stdint.h>
#ifdef NORMAL_PACK
#undef NORMAL_PACK
#endif
#define NORMAL_PACK(x, y, z)                                                   \
  (u32)(((u32)(x) & 0x3FF) | (((u32)(y) & 0x3FF) << 10) |                      \
        (((u32)(z) & 0x3FF) << 20))

#include "utils.h"

#define AMBIENT_RATIO 0.5
#define OUTLINE_SIZE 16 // Épaisseur des arêtes
#define MIN (-OUTLINE_SIZE)
#define MAX (inttov16(1) + OUTLINE_SIZE)

// initialise le rendu 3D de Quads
void startingDraw(bool cullback, int TextureID);

void setFog(int renderDistance);

// dessine un bloc entier
void drawCube(bool cullback, vec2_t t, int TextureID);

// dessine sur le rendu 3D une face
void drawCubeTop(vec2_t t, uint8_t angle);
void drawCubeBottom(vec2_t t, uint8_t angle);
void drawCubeLeft(vec2_t t, uint8_t angle);
void drawCubeRight(vec2_t t, uint8_t angle);
void drawCubeFront(vec2_t t, uint8_t angle);
void drawCubeBack(vec2_t t, uint8_t angle);

// dessine un contour noir autour du bloc que l'on regarde
// si il est dans notre rayon d'action
void drawBlockOutline(int x, int y, int z);

#endif