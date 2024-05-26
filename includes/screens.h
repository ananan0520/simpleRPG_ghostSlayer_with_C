
#ifndef SAMPLE_SCREENS_H
#define SAMPLE_SCREENS_H

#include <raylib.h>
#include "game.h"

void DrawStartupScreen(void);
void DrawMenuScreen (void);
void DrawInGameScreen(Ogre *ogre, Ghost *ghosts, unsigned ghost_num, Texture2D map);
void DrawLoadSavedScreen(SavedGame **game);
void LoadAndPlay (Ogre *ogre, Ghost *ghosts, unsigned ghost_num, Texture2D map, SavedGame *game);
void DrawExitScreen(void);
void DrawCenteredText(int positionY, const char* text, int fontSize, Color color);
bool CenteredButton (float y, const char* text);
void ReturnToMainMenu (int x, int y);
bool isRectHovered (Rectangle rect);
void DimScreen (float alpha);

#endif //SAMPLE_SCREENS_H
