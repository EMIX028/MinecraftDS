#ifndef HUD_H
#define HUD_H

#include <stdio.h>
#include <nds.h>
#include <stdint.h>
#include "PlayerStruct.h"
#include "Blocks.h"

extern PrintConsole hudConsole;
extern PrintConsole subConsole;

// Doit être appelée avant glInit() (elle configure juste le mode vidéo + VRAM)
void initMainScreen3D(bool withText, bool withSprites);

// Console texte pour l'écran du haut (à appeler après videoSetMode, avant la boucle)
void initMainScreenText();

// Sprites pour l'écran du haut (à appeler après videoSetMode, avant la boucle)
void initMainScreenSprites();

void initSubScreen(bool withText, bool withSprites);

//fonction d'affichage d'information sur l'écran du bas de la DS
void SubScreenInfos(char *pseudo, blockId_t indexB);

void MainScreenInfos(player_t *player);
#endif