#include "mctypes.h"

#define AMBIENT_RATIO 0.5

void drawCube(bool cullback,rgb_t color);

void drawSpecialCube(bool cullback);

void drawCubeTop(bool cullback,rgb_t color);
void drawCubeBottom(bool cullback,rgb_t color);
void drawCubeLeft(bool cullback,rgb_t color);
void drawCubeRight(bool cullback,rgb_t color);
void drawCubeFront(bool cullback,rgb_t color);
void drawCubeBack(bool cullback,rgb_t color);