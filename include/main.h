#ifndef MAIN_H
#define MAIN_H


#include <stdint.h>
#include <sys/types.h>
#define GRAVITY 0.008f

//fonction d'affichage d'information sur l'écran du bas de la DS
void subscreenAff(char *pseudo);

//active une lumière pour la caméra ainsi que le transfert d'info
//de la structure camera du joueur au module GluLookAt
void setCam();

//applique le calcul de la gravité au joueur
void ApplyGravity(int size);

//calcul le timer du jeu et les fps
void updatePerformance(void);

//recalcul les faces visibles des chunks
void calculRenderView();

//créer la map temporaire pour le jeu
void setPlayground();

//récupère le pseudo du joueur qu'il a inscrit dans la DS
char *GetPlayerName(char *name);

#endif