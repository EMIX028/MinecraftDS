//ici sera mis toute les constantes utilisé dans le jeu
#ifndef CONFIG_H
#define CONFIG_H

//activer ou non le debug mode
#define DEBUG_MODE false


// définition de nullptr pour la norme de compilation de blocksDS
#if !defined(__nullptr_t_defined) && !defined(_NULLPTR_T) && (__STDC_VERSION__ < 202311L)
    #if defined(__nullptr) || defined(__GNUC__) && (__GNUC__ >= 13)
        typedef __typeof__(nullptr) nullptr_t;
    #else
        typedef struct { } *nullptr_t;
        #define nullptr ((nullptr_t)0)
    #endif
#endif

#define ATTR_FUN_INI __attribute__((section(".itcm")))



#define SCREEN_W 256
#define SCREEN_H 192

#define MAIN_TEXT true
#define MAIN_SPRITE true
#define SUB_TEXT true
#define SUB_SPRITE true
#define CULLBACK true


#define L_CHUNK 16 // chunk minecraft 16
#define H_CHUNK 20 // hauteur max 256

#define GRAVITY divf32(F32_ONE, inttof32(125)) //0.008
//~1.307 bloc par frame car 1.307*60 ~= 78.4 bloc/s (vitesse de chute terminale d'un joueur minecraft)
#define TERMINAL_SPEED divf32(inttof32(-1307),inttof32(1000))


#define P_SPEED divf32(F32_ONE,inttof32(10)) // 0.1
#define P_SENSI 624 //divf32(inttof32(3),inttof32(50)) // 0.06
#define P_FLYSPEED divf32(F32_ONE,inttof32(4)) //0.25
#define P_hitbox divf32(inttof32(3),inttof32(5)) //0.6
#define P_REACH divf32(inttof32(9),inttof32(2)) //4.5
#define DELAY 11 // nb en tour de boucle
#define MAX_ANGLE 14602 //divf32(inttof32(7),inttof32(5)) //1.4

#define P_HEIGHT divf32(inttof32(81),inttof32(50)) // 81/50 = 1.62

//Enum de plusieurs ID de bloc et leur affichage
#define BLOCK_LIST(X)                         \
  X(AIR,            "Air")                    \
  X(STONE,          "Stone")                  \
  X(DIRT,           "Dirt")                   \
  X(GRASS,          "Grass block")            \
  X(COBBLESTONE,    "Cobblestone")            \
  X(OAK_PLANK,      "Oak Plank")              \
  X(BEDROCK,        "Bedrock")                \
  X(SAND,           "Sand")                   \
  X(GOLD_ORE,       "Gold Ore")               \
  X(IRON_ORE,       "Iron Ore")               \
  X(COAL_ORE,       "Coal Ore")               \
  X(OAK_LOG,        "Oak Log")                \
  X(OAK_LEAVE,      "Oak Leave")              \
  X(GLASS,          "Glass")                  \
  X(OBSIDIAN,       "Obsidian")               \
  X(DIAMOND_ORE,    "Diamond Ore")            \
  X(CRAFTING_TABLE, "Crafting table")         \
  X(FURNACE,        "Furnace")                \
  X(REDSTONE_ORE,   "Redstone Ore")

enum Blocks {
#define X(id, name) id,
  BLOCK_LIST(X)
#undef X
  BLOCK_COUNT
};

#endif