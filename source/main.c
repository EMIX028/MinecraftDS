#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "main.h"
#include "HUD.h"
#include "ChunkStruct.h"
#include "player.h"
#include "Blocks.h"
#include "TextureAtlas.h"
#include "keyAssignation.h"
#include "utils.h"

player_t Joueur;
blockId_t indexB = DIRT;
int delay = 0; //delay entre chaque bloc posé ou cassé
bool majChunk = true;
const u8 RenderDistance = 2;

#define SIZE 4
chunk_t chunkL[SIZE] = {
  (chunk_t){.position.x = 0, .position.z = 0},
  (chunk_t){.position.x = -1, .position.z = 0},
  (chunk_t){.position.x = 0, .position.z = -1},
  (chunk_t){.position.x = -1, .position.z = -1}
};


int main() {  
  setPlayer(&Joueur);
  InitBlocks();
  powerOn(POWER_ALL_2D | POWER_3D_CORE | POWER_MATRIX);

   //MAIN : 3D + texte + sprites
  initMainScreen3D(true, true);
  glInit();
  initMainScreenText();
  initMainScreenSprites();
  glClearColor(10, 20, 31, 31);

  //SUB : texte + sprites
  initSubScreen(true, true);

  glEnable(GL_TEXTURE_2D);
  glEnable(GL_ANTIALIAS);
  glEnable(GL_BLEND);

  glViewport(0, 0, SCREEN_W - 1, SCREEN_H - 1);
  glMatrixMode(GL_PROJECTION);
  gluPerspective(70, (float)SCREEN_W / (float)SCREEN_H, 0.1, L_CHUNK*RenderDistance);
  

  char pseudo[PersonalData->nameLen+1];
  GetPlayerName(pseudo);

  int TextureID;

  glGenTextures(1, &TextureID);
  glBindTexture(0, TextureID);

  if (glTexImage2D(
    0,
    0,
    GL_RGBA,
    TEXTURE_SIZE_256,
    TEXTURE_SIZE_256,
    0,
    TEXGEN_TEXCOORD,
    TextureAtlasBitmap
  ) == 0){
    printf("\nerreur init texture\n");
  }

  setPlayground();

  movePlayer(&Joueur,(vec3_t){.x = 0.0f,.y = 5.0f,.z=0.0f}); 



  while (pmMainLoop()) {
    scanKeys();
    loadPlayerMovement(&Joueur,chunkL,SIZE,gBlocks,HitboxBlocks);
    loadKeyAssignation(&Joueur);

    SubScreenInfos(pseudo, indexB);
    MainScreenInfos(&Joueur);

    glBindTexture(0, TextureID);

    ApplyGravity();

    glMatrixMode(GL_MODELVIEW); // reset complet chaque frame
    glLoadIdentity();
    setCam(&Joueur);

    playerInterract(&Joueur, chunkL, SIZE, indexB,gBlocks,
                    (const bool) specialmode, &majChunk, &delay);
    

    calculRenderView();

    for(u8 i = 0 ; i < SIZE ; i++){
      RenderChunk(&chunkL[i],gBlocks,true,&Joueur);
    }

    if(delay > 0){
      --delay;
    }

    glFlush(0);
    oamUpdate(&oamMain);
    oamUpdate(&oamSub);
    swiWaitForVBlank();
  }
  return EXIT_SUCCESS;
}






char *GetPlayerName(char *pseudo){
  void *s = PersonalData->name;
  for (uint16_t *p = s; p < (uint16_t*)s + PersonalData->nameLen; ++p) {
    pseudo[p - (uint16_t*)s] = *p;
  }
  pseudo[PersonalData->nameLen] = '\0';
  return pseudo;
}


void ApplyGravity(){
    const vec3_t gravityMove = {
        .x = 0.0f,
        .y = Joueur.velocityY,
        .z = 0.0f
    };

    if (canMovePlayer(&Joueur, gravityMove,
                      chunkL, SIZE, gBlocks, HitboxBlocks)){
        movePlayer(&Joueur, gravityMove);
    }
    else{
        if (Joueur.velocityY < 0.0f){
            Joueur.velocityY = 0.0f;
            Joueur.isfalling = false;
            Joueur.Position.y = floor(Joueur.Position.y);
        }
        else if (Joueur.velocityY > 0.0f){
            Joueur.velocityY = 0.0f;
        }
    }
    Joueur.velocityY -= GRAVITY;
}


void calculRenderView(){
  if(majChunk){
    blockVisibility(chunkL, SIZE, gBlocks);
    majChunk = false;
  }
}


void setPlayground(){
    for(int i = 0 ; i < SIZE ; ++i){
      initChunk(&chunkL[i],AIR);
      for(int x = 0 ; x < L_CHUNK ; ++x){
        for(int z = 0; z < L_CHUNK ; ++z){
          chunkL[i].blocks[x][0][z].id = BEDROCK;
          chunkL[i].blocks[x][1][z].id = GRASS;
        }
      }
    }
  majChunk = true;
  calculRenderView();
}