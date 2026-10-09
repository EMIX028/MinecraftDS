#include "spriteManager.h"

void setCrosshair() {
    u16 *crosshairVFX = oamAllocateGfx(&oamMain, SpriteSize_8x8, SpriteColorFormat_256Color);
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

void setBackground(){
    u16 *backgroundVFX = oamAllocateGfx(&oamSub, SpriteSize_32x32, SpriteColorFormat_256Color);
    dmaCopy(backgroundTiles, backgroundVFX, backgroundTilesLen);
    dmaCopy(backgroundPal, SPRITE_PALETTE_SUB, backgroundPalLen);
    
    int i = 0; // (SCREEN_W/32)*(SCREEN_H/32) = 48 id utilisé
    for(int x = 0; x < SCREEN_W/32; ++x){
        for(int y = 0; y < SCREEN_H/32; ++y){
            oamSet(&oamSub, i,                        // slot sprite
                x*32, y*32, // x, y
                -1,                                  // priorité (0 = devant)
                0,                                  // id palette étendue
                SpriteSize_32x32, SpriteColorFormat_256Color, backgroundVFX, -1,
                false,        // pas de rotation/scale
                false,        // hide
                false, false, // hflip, vflip
                false);
            ++i;
        }
    }
}