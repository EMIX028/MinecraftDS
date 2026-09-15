#ifndef MAIN_H
#define MAIN_H


#include <stdint.h>
#define GRAVITY 0.008f
#define MAIN_TEXT true
#define MAIN_SPRITE true
#define SUB_TEXT true
#define SUB_SPRITE true

//applique le calcul de la gravité au joueur
void ApplyGravity();

//recalcul les faces visibles des chunks
void calculRenderView();

//créer la map temporaire pour le jeu
void setPlayground();

//récupère le pseudo du joueur qu'il a inscrit dans la DS
char *GetPlayerName(char *name);

#endif