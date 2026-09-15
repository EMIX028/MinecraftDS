#ifndef HUD_H
#define HUD_H

#include <stdio.h>
#include <nds.h>
#include <stdint.h>
#include "PlayerStruct.h"
#include "Blocks.h"

extern PrintConsole hudConsole;
extern PrintConsole subConsole;

void initSubBG(bool WithText, bool WithSprites);

void initMainBG(bool WithText, bool WithSprites);

//fonction d'affichage d'information sur l'écran du bas de la DS
void SubScreenInfos(char *pseudo, blockId_t indexB);

void MainScreenInfos(player_t *player);
#endif