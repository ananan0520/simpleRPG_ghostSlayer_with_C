#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#include "screens.h"
#include "main.h"
#include "loadGame.h"

// Draw text at the centre of the screen with specified position at y-axis
void DrawCenteredText(int positionY, const char* text, int fontSize, Color color) {
    int textWidth = MeasureText(text, fontSize);
    DrawText(text, GetScreenWidth() / 2 - textWidth / 2, positionY - fontSize / 2,
             fontSize, color);
}

// Utility function to check is a rectangle is hovered by mouse
bool isRectHovered (Rectangle rect) {
    return CheckCollisionPointRec(GetMousePosition(), rect);
}

// Draw button at the centre of the screen, return true if clicked
bool CenteredButton (float y, const char* text) {
    Color ButtonColor = WHITE;
    Color ButtonHighlight = SKYBLUE;
    Color ButtonPressColor = DARKBLUE;

    float const ButtonFontSize = 60;
    float const ButtonBorder = 10;

    float textWidth = (float) MeasureText(text, (int) ButtonFontSize);

    float textXOri = (float) GetScreenWidth() / 2.0f - textWidth / 2.0f;
    float textYOri = (float) y - ButtonFontSize / 2.0f;

    Rectangle buttonRect = {
            textXOri - ButtonBorder,
            textYOri - ButtonBorder,
            textWidth + (ButtonBorder * 2.0f),
            ButtonFontSize + (ButtonBorder * 2.0f)
    };

    bool hovered = isRectHovered(buttonRect);
    bool down = hovered && IsMouseButtonDown(MOUSE_BUTTON_LEFT);

    Color color = hovered ? (down ? ButtonPressColor : ButtonHighlight) : (ButtonColor);

    DrawRectangleRec(buttonRect, ColorAlpha(color, 0.25f));
    DrawText(text, (int) textXOri, (int) textYOri, (int) ButtonFontSize, color);
    DrawRectangleLinesEx(buttonRect, 2, color);

    bool clicked = hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

    return clicked;
}

// Draw return button without input handling
bool ReturnButton(float x, float y) {
    const float ButtonWidth = 200;
    const float ButtonHeight = 100;

    Rectangle buttonRect = {
            x,
            y,
            ButtonWidth,
            ButtonHeight
    };

    bool hovered = isRectHovered(buttonRect);

    // Draw button rectangle
    DrawRectangleRec(buttonRect, hovered ? GRAY : DARKGRAY);

    // Draw button text
    DrawText("Return", (int)(x + ButtonWidth / 2 - MeasureText("Return", 40) / 2), (int)(y + ButtonHeight / 2 - 15), 40, WHITE);

    // Check if button is clicked
    bool clicked = hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    return clicked;
}

// Render startup screen
void DrawStartupScreen() {
    DrawCenteredText(GetScreenHeight() / 2, "Wraith Slayer", 200, WHITE);
    DrawCenteredText(GetScreenHeight() / 10 * 9, "Press [ENTER] to Continue", 40, RAYWHITE);
}

// Render main menu
void DrawMenuScreen() {
    DrawCenteredText(GetScreenHeight() / 10 * 3, "Wraith Slayer", 200, WHITE);

    // Go to different screen

    if(CenteredButton((float) GetScreenHeight() / 10 * 5, "Play Game")){
        StartGame();
    }
    if (CenteredButton((float) GetScreenHeight() / 10 * 6, "Load Game")) {
        LoadGameScreen();
    }
    if (CenteredButton((float) GetScreenHeight() / 10 * 7, "Exit")) {
        ExitingGame();
    }
}

// Create return to main menu button, return true if clicked
void ReturnToMainMenu (int x, int y) {
    if (ReturnButton(x, y) || IsKeyPressed(KEY_ESCAPE)) {
        ToMainMenu();
    }
}

// Create return to pause menu button, return true if clicked
void ReturnToPauseMenu (int x, int y) {
    if (ReturnButton(x, y) || IsKeyPressed(KEY_ESCAPE)) {
        ShowPauseMenu();
    }
}

// Dim screen
void DimScreen (float alpha) {
    DrawRectangle(0, 0,
                  GetScreenWidth(), GetScreenHeight(),
                  ColorAlpha(BLACK, alpha));
}

// Render in-game screen
void DrawInGameScreen(Ogre *ogre, Ghost *ghosts, unsigned ghost_num, Texture2D map) {
    RenderGame(ogre, ghosts, ghost_num, map, NULL);
}

// Render in-game screen with selected saved game
void LoadAndPlay (Ogre *ogre, Ghost *ghosts, unsigned ghost_num, Texture2D map, SavedGame *game) {
    RenderGame(ogre, ghosts, ghost_num, map, game);
}

// Draw saved game screen and handle mouse click input to select desired saved game slot
void DisplaySavedGames(const char *directory, SavedGame **game) {
    int numGames;
    SavedGame *games = FetchSavedGames(directory, &numGames);

    if (games != NULL) {
        for (int i = 0; i < numGames; i++) {
            int width = GetScreenWidth() * 0.6;
            int height = 140;
            int PosX = GetScreenWidth() * 0.2;
            int PosY = GetScreenHeight() * 0.15 + 150 * (i + 1);

            Rectangle saveRect = {PosX, PosY, width, height};
            DrawRectangleRec(saveRect, GRAY);

            if (isRectHovered(saveRect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                *game = &games[i];  // Update the pointer passed into this function to point to the selected game
                PlaySavedGame();
            }

            DrawText(TextFormat("Name: Game %s", games[i].fileName),PosX + 30, PosY + 10, 30, RAYWHITE);
            DrawText(TextFormat("Level: %s", games[i].level),PosX + 30, PosY + 10 + 30, 30, RAYWHITE);
            DrawText(TextFormat("PosX: %s", games[i].positionX),PosX + 30, PosY + 10 + 30 * 2, 30, RAYWHITE);
            DrawText(TextFormat("PosY: %s", games[i].positionY),PosX + 30, PosY + 10 + 30 * 3, 30, RAYWHITE);
        }
    }

    free(games);
}

// Draw load game screen
void DrawLoadSavedScreen (SavedGame **game) {
    ReturnToPauseMenu(50, 50);

    DrawCenteredText(GetScreenHeight() / 10 * 2, "Saved Games", 150, WHITE);

    char directory[30] = "saveGame/";

    DisplaySavedGames(directory, game);
}

// Draw exit game screen
void DrawExitScreen() {
    ReturnToMainMenu(50, 50);

    DrawCenteredText(GetScreenHeight() / 10 * 3, "Exit Application", 100, WHITE);
    DrawCenteredText(GetScreenHeight() / 10 * 5, "Are you sure to", 60, WHITE);
    DrawCenteredText(GetScreenHeight() / 10 * 6, "leave the game?", 60, WHITE);

    if (CenteredButton((float) GetScreenHeight() / 10 * 8, "Exit")) {
        ExitGame();
    }
}