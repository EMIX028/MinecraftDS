#include <math.h>
#include <stdint.h>
#include <stdio.h>

#include "Blocks.h"
#include "ChunkStruct.h"
#include "HUD.h"
#include "TextureAtlas.h"
#include "keyAssignation.h"
#include "main.h"
#include "player.h"
#include "spriteManager.h"
#include "utils.h"
#include "mesh.h"

player_t DTCM_BSS Joueur;
int delay = 0; // delay entre chaque bloc posé ou cassé
const u8 RenderDistance = 2;
u8 GameState = RUNNING;

#define SIZE 4
chunk_t chunkL[SIZE] = {(chunk_t){.position.x = 0, .position.z = 0},
                        (chunk_t){.position.x = -1, .position.z = 0},
                        (chunk_t){.position.x = 0, .position.z = -1},
                        (chunk_t){.position.x = -1, .position.z = -1}};

int main() {
  setPlayer(&Joueur);
  InitBlocks();

  powerOn(POWER_ALL_2D | POWER_3D_CORE | POWER_MATRIX);
  initMainBG(MAIN_TEXT, MAIN_SPRITE);
  initSubBG(SUB_TEXT, SUB_SPRITE);

  // couleur approximative du ciel dans minecraft
  glClearColor(15, 25, 31, 31);

  glEnable(GL_TEXTURE_2D);
  glEnable(GL_ANTIALIAS);
  glEnable(GL_BLEND);

  glViewport(0, 0, SCREEN_W - 1, SCREEN_H - 1);
  glMatrixMode(GL_PROJECTION);
  gluPerspective(70, (float)SCREEN_W / (float)SCREEN_H, 0.1,
                 L_CHUNK * RenderDistance);

  char pseudo[PersonalData->nameLen + 1];
  GetPlayerName(pseudo);

  setCrosshair();
  setBackground();

  int TextureID;

  glGenTextures(1, &TextureID);
  glBindTexture(0, TextureID);

  if (glTexImage2D(0, 0, GL_RGBA, TEXTURE_SIZE_256, TEXTURE_SIZE_256, 0,
                   TEXGEN_TEXCOORD, TextureAtlasBitmap) == 0) {
    printf("\nerreur init texture\n");
  }

  setPlayground();

  movePlayer(&Joueur, (f32vec3_t){.x = 0, .y = inttof32(5), .z = 0});

  while (1) {
    scanKeys();
    loadKeyAssignation(&Joueur, &GameState);

    SubScreenInfos(pseudo, Joueur.index, GameState);
    MainScreenInfos(&Joueur);
    
    if(GameState == PAUSED){
      goto Fin_de_Boucle;
    }
    loadPlayerMovement(&Joueur, chunkL, SIZE, gBlocks, HitboxBlocks);
    

    applyGravity(&Joueur, chunkL, SIZE);

    glMatrixMode(GL_MODELVIEW); // reset complet chaque frame
    glLoadIdentity();
    setCam(&Joueur);

    playerInterract(&Joueur, chunkL, SIZE, gBlocks,
                    (const bool)specialmode, &delay);
    
    //rendu 3D
    startingDraw(CULLBACK, TextureID);
    for(chunk_t *cp = chunkL ; cp < chunkL + SIZE ; cp++){
      RenderChunk(cp, gBlocks, true, TextureID, &Joueur);
    }
    endingDraw;

    if (delay > 0) {
      --delay;
    }
Fin_de_Boucle:
    fin_boucle;
  }
  
  if(glDeinit() == 0){
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

char *GetPlayerName(char *pseudo) {
  s16 *s = PersonalData->name;
  for (s16 *p = s; p < s + PersonalData->nameLen; ++p) {
    pseudo[p - s] = *p;
  }
  pseudo[PersonalData->nameLen] = '\0';
  return pseudo;
}

void setPlayground() {
  for (int i = 0; i < SIZE; ++i) {
    initChunk(&chunkL[i], AIR);
    for (int x = 0; x < L_CHUNK; ++x) {
      for (int z = 0; z < L_CHUNK; ++z) {
        chunkL[i].blocks[x][0][z].id = BEDROCK;
        chunkL[i].blocks[x][1][z].id = GRASS;
      }
    }
  }
  chunkVisibility(chunkL, SIZE, gBlocks);
}