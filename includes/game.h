
#ifndef SAMPLE_GAME_H
#define SAMPLE_GAME_H

#include <raylib.h>
#include "loadGame.h"

typedef struct PlayerState {
    unsigned level, currentExp, maxExp, healthRegen;
    float health, maxHealth, atk, armor;
} playerState;

typedef struct EnemyState {
    unsigned level, expDrop, healthRegen;
    float health, maxHealth, atk, armor;
} enemyState;

typedef struct Player {
    Texture Texture_move, Texture_attack, ActiveTexture;
    Sound ogreDead, ogreAtk1, ogreAtk2;
    Rectangle frameRect_move, frameRect_attack, ActiveFrameRect;
    Vector2 position, velocity;
    unsigned
            numFrames_move, numFrames_attack,
            frameWidth_move, frameWidth_attack;
    float speed;
    unsigned attackCD, maxAttackCD, respawnCounter, respawnCD;
    bool playAttackAnimation, IsAlive;
    playerState *state;
} Ogre;

typedef struct Enemy {
    unsigned id;
    Texture Texture_move, Texture_attack, Texture_idle, ActiveTexture;
    Sound ghostSound1, ghostSound2, ghostDying, ghostAtk1, ghostAtk2;
    Rectangle frameRect;
    Vector2 position, velocity;
    unsigned numFrames, frameWidth;
    float speed;
    unsigned attackCD, maxAttackCD, respawnCounter, respawnCD;
    bool playAttackAnimation, IsAlive;
    enemyState *state;
} Ghost;

void InitGameResources(Ogre **ogre, Ghost **ghosts, unsigned ghost_num, Texture2D *map);
void RenderGame(Ogre *ogre, Ghost *ghosts, unsigned ghost_num, Texture2D map, SavedGame *game);
void CleanUpGameResources(Ogre *ogre, Ghost *ghosts);

#endif //SAMPLE_GAME_H
