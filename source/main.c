#include <stdbool.h>
#include <stdlib.h>
#include <nds.h>
#include <stdio.h>
#include "mesh.h"
#include "main.h"
#include "player.h"
#include "ChunkStruct.h"
#include "keyAssignation.h"
#include "Blocks.h"
#include "TextureAtlas.h"


#define GRAVITY 0.05f
player_t Joueur;

int main() {
  setPlayer(&Joueur);
  InitBlocks();
  powerOn(POWER_ALL_2D | POWER_3D_CORE | POWER_MATRIX);
  videoSetMode(MODE_0_3D);
  glInit();
  vramSetBankA(VRAM_A_TEXTURE);
  glClearColor(10, 20, 31, 31); // fond bleu ciel
  consoleDemoInit();
  BG_PALETTE_SUB[0] = RGB15(10,17,10); //fond écran sub
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_ANTIALIAS);
  glViewport(0, 0, SCREEN_W - 1, SCREEN_H - 1);
  glMatrixMode(GL_PROJECTION);
  gluPerspective(70, (float)SCREEN_W / (float)SCREEN_H, 0.1, 40);

  int TextureID;

  glGenTextures(1, &TextureID);
  glBindTexture(0, TextureID);

  if (glTexImage2D(
    0,
    0,
    GL_RGB,
    TEXTURE_SIZE_32,
    TEXTURE_SIZE_32,
    0,
    TEXGEN_TEXCOORD,
    TextureAtlasBitmap
  ) == 0){
    printf("\nerreur init texture\n");
  }

  chunk_t chunk00 = {
    .position.x = 0, .position.z = 0
  };

  chunk_t chunkTest = {
    .position.x = 1, .position.z = 0
  };
  initChunk(&chunkTest,STONE);
  initChunk(&chunk00,AIR);

  chunk00.blocks[5][1][5] = DIRT;
  chunk_t *chunk_list[] = {&chunk00,&chunkTest};
  bool contour[9] = {false};

  uint8_t compteur = 0;
  movePlayer(&Joueur,(vec3_t){.x = 0,.y = 1,.z=0});

  while (pmMainLoop()) {
    glBindTexture(0, TextureID);
    subscreenAff();
    scanKeys();
    loadPlayerMovement(&Joueur,contour[0]);
    loadKeyAssignation(&Joueur);

    // Joueur.velocityY -= GRAVITY;
    // movePlayer(&Joueur,(vec3_t){.x=0,.y=Joueur.velocityY,.z=0});

    if(keysDown() & KEY_R){
      chunkTest.blocks[compteur][1][5] = AIR;
      ++compteur;
    }
    if((keysHeld() & KEY_L) && (keysDown() & KEY_A)){
      chunkTest.blocks[compteur][1][5] = COBBLESTONE;
      --compteur;
    }


    glMatrixMode(GL_MODELVIEW); // reset complet chaque frame
    glLoadIdentity();


    glLight(
      0,
      RGB15(31,31,31),
      floattov10(-0.5f),
      floattov10(-1.0f),
      floattov10(-0.3f)
    );

    glMaterialf(GL_AMBIENT, RGB15(15,15,15));
    glMaterialf(GL_DIFFUSE, RGB15(31,31,31));

    gluLookAt(
      Joueur.Camera.position.x, Joueur.Camera.position.y, Joueur.Camera.position.z,
      
      Joueur.Camera.position.x + Joueur.Direction.x, Joueur.Camera.position.y +Joueur.Direction.y, Joueur.Camera.position.z + Joueur.Direction.z,

      0.0f, 1.0f, 0.0f
    );

    hitbox_t cube = {.d=1,.h=1,.w=1};

    bool cubeTest = checkCollisionTest(Joueur.Position,Joueur.hitbox,
                                                (ivec3_t){.x=5,.y=1,.z=5},
                                              cube);


    //printf("\nposition local x : %d chunk x: %d\n",(int)(Joueur.Position.x)%L_CHUNK,(int)(Joueur.Position.x)/L_CHUNK);

    // for(int i =0; i<2;++i){
    //   if((int)(Joueur.Position.x)/L_CHUNK == chunk_list[i]->position.x &&
    //       (int)(Joueur.Position.z)/L_CHUNK == chunk_list[i]->position.z){
    //         if((int)(Joueur.Position.x)%L_CHUNK != 0 &&
    //             (int)(Joueur.Position.x)%L_CHUNK != L_CHUNK-1 &&
    //             (int)(Joueur.Position.z)%L_CHUNK != 0 &&
    //             (int)(Joueur.Position.z)%L_CHUNK != L_CHUNK-1){
    //               contour[0] = checkCollisionPlayerToBlock(Joueur.Position,
    //                                                         Joueur.hitbox,
    //                                                       (ivec3_t){.x = (int)Joueur.Position.x,
    //                                                               .y=(int)Joueur.Position.y,
    //                                                               .z=(int)(Joueur.Position.z+1)},
    //                                                       (hitbox_t){.d=1,.h=1,.w=1}) && 
    //                                                       gBlocks[chunk_list[i]->blocks[(int)(Joueur.Position.x)%L_CHUNK][(int)(Joueur.Position.y)%H_CHUNK][(int)(Joueur.Position.z)%L_CHUNK+1]].solid;
    //       }
    //   }
    // }
    if(cubeTest==true){
      printf("\n\tCollision\n");
    }

    RenderChunk(&chunk00,gBlocks);
    RenderChunk(&chunkTest,gBlocks);

    glFlush(0);
    swiWaitForVBlank();
  }
  return EXIT_SUCCESS;
}

void subscreenAff(){
  consoleClear();
  BG_PALETTE_SUB[255] = RGB15(10, 10, 10);
  iprintf("\x1b[1;5H|Minecraft DS Edition|");
  iprintf("\x1b[2;5H----------------------");
  printf("\nx:%4f y:%4f z:%4f",
          Joueur.Position.x,
          Joueur.Position.y,
          Joueur.Position.z);
}