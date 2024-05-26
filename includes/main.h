#ifndef SAMPLE_MAIN_H
#define SAMPLE_MAIN_H

enum ApplicationState {
    Startup,
    Menu,
    InGame,
    LoadScreen,
    LoadSavedGame,
    GamePaused,
    Quitting,
    Quit
};

void StartGame(void);
void PlaySavedGame (void);
void LoadGameScreen (void);
void ExitGame (void);
void ToMainMenu (void);
void ShowPauseMenu (void);
void ExitingGame(void);

#endif //SAMPLE_MAIN_H