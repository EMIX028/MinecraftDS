#include "mctypes.h"

#define AMBIENT_RATIO 0.5

void drawCube(bool cullback,vec2_8_t t);

void drawSpecialCube(bool cullback);

void drawCubeTop(bool cullback, vec2_8_t t);
void drawCubeBottom(bool cullback, vec2_8_t t);
void drawCubeLeft(bool cullback, vec2_8_t t);
void drawCubeRight(bool cullback, vec2_8_t t);
void drawCubeFront(bool cullback, vec2_8_t t);
void drawCubeBack(bool cullback, vec2_8_t t);