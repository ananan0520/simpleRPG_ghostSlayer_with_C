#include "gameHUD.h"
#include "screens.h"
#include "main.h"

#include <stdio.h>
#include <raylib.h>
#include <dirent.h>

// Draw ghost information
void DisplayMonsterInformation(Rectangle TopBarRect, Ghost ghost) {
    const int textFontSize = 30;
    const float levelX = TopBarRect.x + 60;
    const float levelY = TopBarRect.y + 30;

    char level[30];
    unsigned levelNum = ghost.state->level;
    snprintf(level, sizeof(level), "Lvl. %d", levelNum);

    const float nameX = levelX + MeasureText(level, textFontSize) + 20;
    const float nameY = levelY;

    char MonsterName[256] = "Ghost";

    DrawText(level, levelX, levelY, textFontSize, DARKBLUE);
    DrawText(MonsterName, nameX, nameY, textFontSize, DARKPURPLE);
}

// Draw ogre information
void DisplayPlayerInformation(Rectangle BottomBarRect, Ogre *ogre) {
    const int textFontSize = 30;
    const float levelX = BottomBarRect.x + 90;
    const float levelY = BottomBarRect.y + 30;

    char level[30];
    unsigned levelNum = ogre->state->level; // todo: get player_level

    snprintf(level, sizeof(level), "Lvl. %d", levelNum);

    DrawText(level, levelX, levelY, textFontSize, DARKBLUE);
}

// Display current ghost health / max health
void DisplayMonsterHealth (const float HealthBarY, Ghost ghost) {
    unsigned ghostHealth = (unsigned) ghost.state->health;
    unsigned ghostMaxHealth = (unsigned) ghost.state->maxHealth;

    char text[30];

    snprintf(text, sizeof(text), "%d / %d", ghostHealth, ghostMaxHealth);

    const int textFontSize = 20;
    float textWidth = (float) MeasureText(text, (int) textFontSize);

    float textXOri = (float) GetScreenWidth() / 2.0f - textWidth / 2.0f;
    float textYOri = (float) HealthBarY;

    DrawText(text, (int) textXOri, (int) textYOri, (int) textFontSize, WHITE);
};

// Display current ogre health / max health
void DisplayPlayerHealth(const float HealthBarY, Ogre *ogre) {
    unsigned ogreHealth = (unsigned) ogre->state->health;
    unsigned ogreMaxHealth = (unsigned) ogre->state->maxHealth;

    char text[30];

    snprintf(text, sizeof(text), "%d / %d", ogreHealth, ogreMaxHealth);

    const int textFontSize = 20;
    float textWidth = (float) MeasureText(text, (int) textFontSize);

    float textXOri = (float) GetScreenWidth() / 2.0f - textWidth / 2.0f;
    float textYOri = (float) HealthBarY;

    DrawText(text, (int) textXOri, (int) textYOri, (int) textFontSize, WHITE);
}

// Draw player health bar
void PlayerHealthBar(Rectangle BottomBarRect, Ogre *ogre) {
    const float HealthBarWidth = BottomBarRect.width * 0.8;
    const float HealthBarHeight = BottomBarRect.height * 0.2;
    const float HealthBarX = BottomBarRect.x + BottomBarRect.width * 0.1;
    const float HealthBarY = BottomBarRect.y + BottomBarRect.height * 0.6;

    Rectangle HealthBarRectEmpty = {
            HealthBarX,
            HealthBarY,
            HealthBarWidth,
            HealthBarHeight
    };

    float healthPercentage = ogre->state->health / ogre->state->maxHealth;

    Rectangle HealthBarRectFilled = HealthBarRectEmpty;
    HealthBarRectFilled.width = HealthBarWidth * healthPercentage;

    DrawRectangleRec(HealthBarRectEmpty, DARKGRAY);
    DrawRectangleRec(HealthBarRectFilled, RED);

    DisplayPlayerHealth(HealthBarY, ogre);
}

// Draw monster health bar
void MonsterHealthBar(Rectangle TopBarRect, Ghost ghost) {
    const float HealthBarWidth = TopBarRect.width * 0.8;
    const float HealthBarHeight = TopBarRect.height * 0.2;
    const float HealthBarX = TopBarRect.x + TopBarRect.width * 0.1;
    const float HealthBarY = TopBarRect.y + TopBarRect.height * 0.6;

    Rectangle HealthBarRectEmpty = {
            HealthBarX,
            HealthBarY,
            HealthBarWidth,
            HealthBarHeight
    };

    float healthPercentage = ghost.state->health / ghost.state->maxHealth;

    Rectangle HealthBarRectFilled = HealthBarRectEmpty;
    HealthBarRectFilled.width = HealthBarWidth * healthPercentage;

    DrawRectangleRec(HealthBarRectEmpty, DARKGRAY);
    DrawRectangleRec(HealthBarRectFilled, RED);

    DisplayMonsterHealth(HealthBarY, ghost);
}

// Draw top bar to collectively display ghost animation
void DrawTopBar (Ghost ghost) {
    const float TopBarHeight = 100;
    const float TopBarWidth = 600;

    Rectangle TopBarRect = {
            (float) GetScreenWidth() / 2 - TopBarWidth / 2,
            0,
            TopBarWidth,
            TopBarHeight
    };

    DrawRectangleRec(TopBarRect, LIGHTGRAY);
    MonsterHealthBar(TopBarRect, ghost);
    DisplayMonsterInformation(TopBarRect, ghost);
}

// Draw bottom bar to collectively display ogre information
void DrawBottomBar(Ogre *ogre) {
    const float BottomBarHeight = 100;
    const float BottomBarWidth = 900;

    Rectangle BottomBarRect = {
            (float) GetScreenWidth() / 2 - BottomBarWidth /2,
            (float) GetScreenHeight() - BottomBarHeight,
            BottomBarWidth,
            BottomBarHeight
    };

    DrawRectangleRec(BottomBarRect, WHITE);
    PlayerHealthBar(BottomBarRect, ogre);

    DisplayPlayerInformation(BottomBarRect, ogre);
}

// Delete oldest saved file in the directory
void DeleteOldSaveFile (char * directory) {
    DIR *dir;
    struct dirent *ent;
    int oldestIndex = 9999;
    char oldestFileName[256] = {0};

    if ((dir = opendir(directory)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            size_t len = strlen(ent->d_name);
            if (len >= 4 && strcmp(ent->d_name + len - 4, ".txt") == 0) { // check is the file .txt
                int fileIndex;
                if (sscanf(ent->d_name, "%d.txt", &fileIndex) == 1) { // get the filename as integer
                    if (fileIndex < oldestIndex) {
                        oldestIndex = fileIndex;
                        snprintf(oldestFileName, sizeof(oldestFileName), "%s%s", directory, ent->d_name);
                    }
                }
            }
        }
        closedir(dir);
    }

    // Debug messages
    if (oldestFileName[0] != '\0') {
        if (remove(oldestFileName) == 0) {
            printf("Deleted oldest save game: %s\n", oldestFileName);
        } else {
            perror("Error deleting oldest save game");
            return;
        }
    }
}

void NewSaveGame (Ogre *ogre) {
    char directory[30] = "saveGame/";
    char fileName[256];

    DIR *dir;
    struct dirent *ent;
    int oldestIndex = 9999;

    if ((dir = opendir(directory)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            size_t len = strlen(ent->d_name);
            if (len >= 4 && strcmp(ent->d_name + len - 4, ".txt") == 0) { // check is the file .txt
                int fileIndex;
                if (sscanf(ent->d_name, "%d.txt", &fileIndex) == 1) { // get the filename as integer
                    if (fileIndex < oldestIndex) {
                        oldestIndex = fileIndex;
                    }
                }
            }
        }
        closedir(dir);
    }

    int savedGameCount = CountSavedGames(directory);

    if (savedGameCount == 0) { // set the index = 0 if there is no saved game in the directory
        oldestIndex = 0;
    }

    int currentSavedName = oldestIndex + 1;

    // Delete if saved game already is 5 before creating a new saved game
    if (savedGameCount >= 5) {
        DeleteOldSaveFile(directory);
    }

    snprintf(fileName, sizeof(fileName), "%s%d.txt", directory, currentSavedName);

    FILE *filePtr = fopen(fileName, "w");

    if (filePtr == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // write information to the saved game file
    fprintf(filePtr, "%d\n%d\n%f\n%f", currentSavedName, ogre->state->level, ogre->position.x, ogre->position.y);

    fclose(filePtr);
}

// Draw pause menu
void TogglePauseMenu (Ogre *ogre) {
    DrawCenteredText(GetScreenHeight() * 0.2, "Pausing", 100, RAYWHITE);

    if (CenteredButton(GetScreenHeight() * 0.4, "Return to Game")) {
        StartGame();
    }
    if (CenteredButton(GetScreenHeight() * 0.5, "Save Game")) {
        NewSaveGame(ogre);
    }
    if (CenteredButton(GetScreenHeight() * 0.6, "Load Game")) {
        LoadGameScreen();
    }
    if (CenteredButton(GetScreenHeight() * 0.7, "Return To Main Menu")) {
        ToMainMenu();
    }
}

// Toggle pause menu is ESC is pressed
void ShortcutKeyHandler (void) {
    if (IsKeyPressed(KEY_ESCAPE)) {
        ShowPauseMenu();
    }
}

// Master function of drawing in-game HUD
void DrawHUD (Ogre *ogre, Ghost *ghost, int nearestGhostIndex) {
    ShortcutKeyHandler();

    if (nearestGhostIndex != -1) { // if there is any ghost nearby
        DrawTopBar(ghost[nearestGhostIndex]);
    }

    DrawBottomBar(ogre);
}