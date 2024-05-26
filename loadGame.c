#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "loadGame.h"

// Calculate the total number of saved file in the specified directory
int CountSavedGames(const char *directory) {
    DIR *dir;
    struct dirent *ent; // declare the directory entry
    int fileCount = 0;


    if ((dir = opendir(directory)) != NULL) {
        // Iterate over all entries in the directory, and
        // Check if directory entry is empty
        while ((ent = readdir(dir)) != NULL) {
            // Check if the dirent is a regular file with a ".txt" extension
            size_t len = strlen(ent->d_name);
            if (len >= 4 && strcmp(ent->d_name + len - 4, ".txt") == 0) {
                fileCount++;
            }
        }
        closedir(dir);
    } else {
        perror("Error opening directory"); // error message to debug
        return 0;
    }

    return fileCount;
}

// Fetch every saved file in the specified directory, and
// Change the value of numGames outside of this function through pointer
SavedGame* FetchSavedGames(const char *directory, int *numGames) {
    DIR *dir;
    struct dirent *ent; // declare the directory entry

    // check for total save file in the directory
    const int savedGameNum = CountSavedGames(directory);
    *numGames = savedGameNum;
    SavedGame *savedGames = malloc(savedGameNum * sizeof(SavedGame));

    // debug message
    if (savedGames == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    int oldestIndex = 9999;
    char oldestFileName[256] = {0};

    // check for the earliest save file
    if ((dir = opendir(directory)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            size_t len = strlen(ent->d_name);
            // check is the file .txt (4 character extension)
            if (len >= 4 && strcmp(ent->d_name + len - 4, ".txt") == 0) {
                int fileIndex;
                // if writing the name of directory entry to fileIndex as integer is successful
                if (sscanf(ent->d_name, "%d.txt", &fileIndex) == 1) {
                    // check if the current fileIndex is smaller than the current oldestIndex
                    if (fileIndex < oldestIndex) {
                        oldestIndex = fileIndex; // replace if true
                        // write into string
                        snprintf(oldestFileName, sizeof(oldestFileName), "%s%s", directory, ent->d_name);
                    }
                }
            }
        }
        closedir(dir);
    }

    int fileCount = 0;
    char fileName[256];

    // open the file and load the content into SavedGame object
    do {
        snprintf(fileName, sizeof(fileName), "%d.txt", oldestIndex + fileCount);
        char filePath[256];
        snprintf(filePath, sizeof(filePath), "%s%s", directory, fileName);

        FILE *file = fopen(filePath, "r");
        if (file == NULL) {
            fprintf(stderr, "Could not open file: %s\n", filePath);
            free(savedGames);
            return NULL;
        }

        if (fscanf(file, "%s %s %s %s", savedGames[fileCount].fileName,
                                                      &savedGames[fileCount].level,
                                                      &savedGames[fileCount].positionX,
                                                      &savedGames[fileCount].positionY) != 4) {
            fprintf(stderr, "Error reading file: %s\n", filePath);
            fclose(file);
            free(savedGames);
            return NULL;
        }

        fclose(file);
        fileCount++;
    } while (fileCount < savedGameNum);

    return savedGames;
}