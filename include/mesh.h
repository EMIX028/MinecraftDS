#include "mctypes.h"

#define AMBIENT_RATIO 0.5

void startingDraw(bool cullback);

void drawCube(bool cullback,vec2_8_t t);

void drawSpecialCube(bool cullback);

void drawCubeTop(vec2_8_t t);
void drawCubeBottom(vec2_8_t t);
void drawCubeLeft(vec2_8_t t);
void drawCubeRight(vec2_8_t t);
void drawCubeFront(vec2_8_t t);
void drawCubeBack(vec2_8_t t);