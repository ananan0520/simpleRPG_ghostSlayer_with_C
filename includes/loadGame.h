
#ifndef SAMPLE_LOADGAME_H
#define SAMPLE_LOADGAME_H

typedef struct {
    char fileName[256];
    char level[256];
    char positionX[256];
    char positionY[256];
} SavedGame;

SavedGame* FetchSavedGames(const char *directory, int *numGames);
int CountSavedGames(const char *directory);

#endif //SAMPLE_LOADGAME_H