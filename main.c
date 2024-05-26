#include <raylib.h>
#include <stdio.h>

#include "main.h"
#include "screens.h"
#include "gameHUD.h"
#include "game.h"

enum ApplicationState AppState;

// Change application state to Menu
void ToMainMenu (void) {
    AppState = Menu;
}

// Change application state to InGame
void StartGame (void) {
    AppState = InGame;
}

// Change application state to LoadScreen
void LoadGameScreen (void) {
    AppState = LoadScreen;
}

// Change application state to LoadSavedGame
void PlaySavedGame (void) {
    AppState = LoadSavedGame;
}

// Change application state to GamePaused
void ShowPauseMenu (void) {
    AppState = GamePaused;
}

// Change application state to Quitting
void ExitingGame (void) {
    AppState = Quitting;
}

// Change application state to Quit
void ExitGame (void) {
    AppState = Quit;
}

// Main function of the program
int main (void) {
    InitWindow(1920, 1080, "Wraith Slayer");

    // Borderless full screen if screen dimension < 2000 * 1500 (small screen)

    if (GetMonitorWidth(GetCurrentMonitor()) < 2000 &&
        GetMonitorHeight(GetCurrentMonitor()) < 1500 ) {
        ToggleBorderlessWindowed();
    }

    SetExitKey(0);
    SetTargetFPS(60);

    // Get ready the resources
    InitAudioDevice();

    SavedGame *currentGame = NULL;

    static unsigned ghost_num = 14;
    Ogre *ogre = NULL;
    Ghost *ghosts = NULL;

    Music currentMusic = {0};
    Music menuBGM = LoadMusicStream("resources/menuBGM.mp3");
    Music inGameBGM = LoadMusicStream("resources/inGameBGM.mp3");

    Texture2D map;

    SetMusicVolume(inGameBGM, .5f);
    currentMusic = menuBGM;

    AppState = Startup;

    bool ProgramShouldClose = false;

    // Main loop
    while (!WindowShouldClose()) {

        PlayMusicStream(currentMusic);
        UpdateMusicStream(currentMusic);

        // control rendering

        BeginDrawing();

        ClearBackground(BLACK);

        switch (AppState) {
            case Startup:
                DrawStartupScreen();
                if (IsKeyPressed(KEY_ENTER)) {
                    AppState = Menu;
                }
                break;
            case Menu:
                static bool menuReloaded = false;
                if (!menuReloaded) {
                    InitGameResources(&ogre, &ghosts, ghost_num, &map);
                    menuReloaded = true;
                }
                DrawMenuScreen();

                if (IsKeyPressed(KEY_ESCAPE)) {
                    ExitGame();
                }

                break;
            case InGame:
                currentMusic = inGameBGM;
                DrawInGameScreen(ogre, ghosts, ghost_num, map);
                break;
            case LoadScreen:
                DrawLoadSavedScreen(&currentGame);
                break;
            case LoadSavedGame:
                currentMusic = inGameBGM;
                LoadAndPlay(ogre, ghosts, ghost_num, map, currentGame);
                break;
            case GamePaused:
                TogglePauseMenu(ogre);

                if (IsKeyPressed(KEY_ESCAPE)) {
                    StartGame();
                }
                break;
            case Quitting:
                DrawExitScreen();
                break;
            case Quit:
                ProgramShouldClose = true;
                break;
        }
        EndDrawing();
        if (ProgramShouldClose) {
            break;
        }
    }

    CleanUpGameResources(ogre, ghosts);
    CloseAudioDevice();
    UnloadMusicStream(menuBGM);
    UnloadMusicStream(inGameBGM);

    CloseWindow();

    return 0;
}