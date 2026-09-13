#include "HUD.h"

PrintConsole hudConsole;
PrintConsole subConsole;

void initMainScreen3D(bool withText, bool withSprites) {
    int flags = MODE_0_3D;
    if (withText)    flags |= DISPLAY_BG3_ACTIVE;
    if (withSprites) flags |= DISPLAY_SPR_ACTIVE | DISPLAY_SPR_1D;

    videoSetMode(flags);

    vramSetBankA(VRAM_A_TEXTURE);

    if (withSprites) {
        vramSetBankB(VRAM_B_MAIN_SPRITE);
    }
    if (withText) {
        vramSetBankE(VRAM_E_MAIN_BG); // <- changé de D à E
    }
}

void initMainScreenText(void){
    consoleInit(&hudConsole, 3, BgType_Text4bpp, BgSize_T_256x256, 4, 1, true, true);
    // priorité : le texte doit passer devant la 3D
    bgSetPriority(hudConsole.bgId, 0); // texte -> devant
    bgSetPriority(0, 1);              // BG0 = layer 3D -> derrière
    
}

void initMainScreenSprites(void){
    oamInit(&oamMain, SpriteMapping_1D_32, false);
}


void initSubScreen(bool withText, bool withSprites){
    int flags = MODE_0_2D;
    if (withSprites) flags |= DISPLAY_SPR_ACTIVE | DISPLAY_SPR_1D;

    videoSetModeSub(flags);

    if (withText){
        vramSetBankC(VRAM_C_SUB_BG);
        consoleInit(&subConsole, 0, BgType_Text4bpp, BgSize_T_256x256, 4, 1, false, true);
    }
    if (withSprites){
        vramSetBankD(VRAM_D_SUB_SPRITE);
        oamInit(&oamSub, SpriteMapping_1D_32, false);
    }
}

//consoleSelect(&subConsole ou &hudConsole); pour choisir l'écran ou afficher le texte

void SubScreenInfos(char *pseudo, blockId_t indexB){
  consoleSelect(&subConsole);
  BG_PALETTE_SUB[0] = RGB15(24,24,24); //fond écran sub
  BG_PALETTE_SUB[255] = RGB15(10, 10, 10); //  couleur texte

  iprintf("\x1b[1;3H|Minecraft DS Edition 1.1a|");
  iprintf("\x1b[2;3H--------------------------");
  iprintf("\x1b[4;1HHey %s !",pseudo);
  iprintf("\x1b[6;0H Block: %s",getBlockName(indexB));
}

void MainScreenInfos(player_t *player){
  consoleSelect(&hudConsole);
  BG_PALETTE[255] = RGB15(30, 30, 30); //couleur texte
  iprintf("\x1b[1;0Hposition x:%3d y:%3d z:%3d",
          (int)player->Position.x,
          (int)player->Position.y,
          (int)player->Position.z);
}