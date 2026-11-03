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
    oamInit(&oamSub, SpriteMapping_1D_128, true);

    // palette stocké dans la VRAM_I
    vramSetBankI(VRAM_I_LCD);

    dmaCopy(backgroundPal, VRAM_I_EXT_SPR_PALETTE[0], backgroundPalLen);

    dmaCopy(Title32P0Pal, VRAM_I_EXT_SPR_PALETTE[1], Title32P0PalLen);
    dmaCopy(Title32P1Pal, VRAM_I_EXT_SPR_PALETTE[2], Title32P1PalLen);
    dmaCopy(Title32P2Pal, VRAM_I_EXT_SPR_PALETTE[3], Title32P2PalLen);
    dmaCopy(Title32P3Pal, VRAM_I_EXT_SPR_PALETTE[4], Title32P3PalLen);

    // Activer les palettes étendues pour le sous-écran
    vramSetBankI(VRAM_I_SUB_SPRITE_EXT_PALETTE);

    u16 *backgroundVFX = oamAllocateGfx(&oamSub, SpriteSize_32x32, SpriteColorFormat_256Color);
    dmaCopy(backgroundTiles, backgroundVFX, backgroundTilesLen);
    dmaCopy(backgroundPal, VRAM_I_EXT_SPR_PALETTE[0], backgroundPalLen);
    
    int i = 0; // (SCREEN_W/32)*(SCREEN_H/32) = 48 id utilisé
    for(int x = 0; x < SCREEN_W / 32; ++x){
        for(int y = 0; y < SCREEN_H / 32; ++y){
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

    u16 *titleP0 = oamAllocateGfx(&oamSub, SpriteSize_32x32, SpriteColorFormat_256Color);
    dmaCopy(Title32P0Tiles, titleP0, Title32P0TilesLen);
    dmaCopy(Title32P0Pal, VRAM_I_EXT_SPR_PALETTE[1], Title32P0PalLen);
    oamSet(&oamSub, 49,                        // slot sprite
                64, 0, // x, y
                0,                                  // priorité (0 = devant)
                1,                                  // id palette étendue
                SpriteSize_32x32, SpriteColorFormat_256Color, titleP0, -1,
                false,        // pas de rotation/scale
                false,        // hide
                false, false, // hflip, vflip
                false);

    u16 *titleP1 = oamAllocateGfx(&oamSub, SpriteSize_32x32, SpriteColorFormat_256Color);
    dmaCopy(Title32P1Tiles, titleP1, Title32P1TilesLen);
    dmaCopy(Title32P1Pal, VRAM_I_EXT_SPR_PALETTE[2], Title32P1PalLen);
    oamSet(&oamSub, 50,                        // slot sprite
                96, 0, // x, y
                0,                                  // priorité (0 = devant)
                2,                                  // id palette étendue
                SpriteSize_32x32, SpriteColorFormat_256Color, titleP1, -1,
                false,        // pas de rotation/scale
                false,        // hide
                false, false, // hflip, vflip
                false);

    u16 *titleP2 = oamAllocateGfx(&oamSub, SpriteSize_32x32, SpriteColorFormat_256Color);
    dmaCopy(Title32P2Tiles, titleP2, Title32P2TilesLen);
    dmaCopy(Title32P2Pal, VRAM_I_EXT_SPR_PALETTE[3], Title32P2PalLen);
    oamSet(&oamSub, 51,                        // slot sprite
                128, 0, // x, y
                0,                                  // priorité (0 = devant)
                3,                                  // id palette étendue
                SpriteSize_32x32, SpriteColorFormat_256Color, titleP2, -1,
                false,        // pas de rotation/scale
                false,        // hide
                false, false, // hflip, vflip
                false);
    
    u16 *titleP3 = oamAllocateGfx(&oamSub, SpriteSize_32x32, SpriteColorFormat_256Color);
    dmaCopy(Title32P3Tiles, titleP3, Title32P3TilesLen);
    dmaCopy(Title32P3Pal, VRAM_I_EXT_SPR_PALETTE[4], Title32P3PalLen);
    oamSet(&oamSub, 52,                        // slot sprite
                160, 0, // x, y
                0,                                  // priorité (0 = devant)
                4,                                  // id palette étendue
                SpriteSize_32x32, SpriteColorFormat_256Color, titleP3, -1,
                false,        // pas de rotation/scale
                false,        // hide
                false, false, // hflip, vflip
                false);
}