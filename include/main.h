#ifndef MAIN_H
#define MAIN_H


#include <stdint.h>

//créer la map temporaire pour le jeu
void setPlayground();

//récupère le pseudo du joueur qu'il a inscrit dans la DS
char *GetPlayerName(char *name);

#define fin_boucle                  \
    {                               \
        glFlush(0);                 \
        swiWaitForVBlank();         \
        if (MAIN_SPRITE)            \
            oamUpdate(&oamMain);    \
        if (SUB_SPRITE)             \
            oamUpdate(&oamSub);     \
    }

#endif