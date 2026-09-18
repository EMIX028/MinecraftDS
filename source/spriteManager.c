#include "spriteManager.h"

void setCrosshair() {
  u16 *crosshairVFX =
      oamAllocateGfx(&oamMain, SpriteSize_8x8, SpriteColorFormat_256Color);
  dmaCopy(CrosshairTiles, crosshairVFX, CrosshairTilesLen);
  dmaCopy(CrosshairPal, SPRITE_PALETTE, CrosshairPalLen);

  oamSet(&oamMain, 0,                        // slot sprite
         SCREEN_W / 2 + 1, SCREEN_H / 2 + 1, // x, y
         0,                                  // priorité (0 = devant)
         0,                                  // id palette étendue
         SpriteSize_8x8, SpriteColorFormat_256Color, crosshairVFX, -1,
         false,        // pas de rotation/scale
         false,        // hide
         false, false, // hflip, vflip
         false);
}