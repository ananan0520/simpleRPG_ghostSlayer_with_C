
#ifndef SAMPLE_GAMEHUD_H
#define SAMPLE_GAMEHUD_H

#include <raylib.h>
#include "game.h"

void DrawHUD(Ogre *ogre, Ghost *ghost, int nearestGhostIndex);
void TogglePauseMenu (Ogre *ogre);

#endif //SAMPLE_GAMEHUD_H
