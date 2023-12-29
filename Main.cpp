#include "raylib.h"
#include "game.h"
#include "Enemy.h"
#include "Player.h"
typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Fast Car");
    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
    Texture2D COEURTexture = (LoadTexture("Skin/COEURvlalesvies.png"));
    Texture2D MenuBar = (LoadTexture("Skin/Menu.png"));
    
    GameScreen currentScreen = LOGO;
    int framesCounter = 0;
    bool GameRun = true;
    Rectangle playButtonRect = { screenWidth / 2-100, screenHeight / 2, 170, 60 };
    Rectangle scoreButtonRect = { screenWidth / 2 - 85, screenHeight / 2 + 80, 170, 60 };
    Rectangle settingsButtonRect = { screenWidth / 2 - 100, screenHeight / 2 + 160, 200, 60 };
    Rectangle ResumeButtonRect = { 290, 100, 230, 55 };
    Rectangle MenuButtonRect = { 295, 200, 230, 55 };
    Rectangle Menubar = { screenWidth - 90, 10, screenWidth - 90+75, 10+75 };
    
    SetTargetFPS(60); 
    Game game(screenWidth, screenHeight);
    while (!WindowShouldClose())   
    {
        if (IsKeyPressed(KEY_F11)) {
            ToggleFullscreen();
        }
        Vector2 mousePos = GetMousePosition();
        if (currentScreen != LOGO)
        {
            UpdateMusicStream(game.music);
        }

        switch (currentScreen)
        {
        case LOGO:
        {

            framesCounter++;  

            // apres 2 sec changement de screen
            if (framesCounter > 120)
            {
                currentScreen = TITLE;
            }
        } break;
        case TITLE:
        {
            Color buttonColor = BLUE;
            
            // Check if "Play" button is clicked
            if (CheckCollisionPointRec(mousePos, playButtonRect)) {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    game.ClearEntities();
                    currentScreen = GAMEPLAY;
                }
            }

            // Check if "Score" button is clicked
            if (CheckCollisionPointRec(mousePos, scoreButtonRect)) {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
                {
                    // TODO: Add code to display the scores window
                    // You can create a function or a separate window manager class for this purpose
                }
            }

            // Check if "Settings" button is clicked
            if (CheckCollisionPointRec(mousePos, settingsButtonRect)) {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    // TODO: Add code to display the settings window
                    // You can create a function or a separate window manager class for this purpose
                }
            }
        } break;
        case GAMEPLAY:
        {
            if (CheckCollisionPointRec(mousePos, ResumeButtonRect)) {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    GameRun = true;
                }
            }
            if (CheckCollisionPointRec(mousePos, MenuButtonRect)) {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    
                    currentScreen = TITLE;
                    game.ClearEntities();
                    game.updateBestScore(game.score);
                }
            }
            if (game.GameOver == true)
           {
                currentScreen = ENDING;
                
           }
        } break;
        case ENDING:
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                game.Reset();
                currentScreen = GAMEPLAY;
            }   
        } break;
        default: break;
        }
        BeginDrawing();

        ClearBackground(RAYWHITE);

        switch (currentScreen)
        {
        case LOGO:
        {
            game.getBestScore();
            DrawText("FAST CAR", screenWidth / 2 - MeasureText("FAST CAR", 40) / 2, screenHeight / 2 - 40, 40, LIGHTGRAY);
            DrawText("WAIT...", screenWidth / 2 - MeasureText("WAIT...", 20) / 2, screenHeight / 2 + 20, 20, GRAY);

        } break;
        case TITLE:
        {
            ClearBackground(GREEN);
            DrawRectangle(screenWidth / 4, 0, screenWidth / 2, screenHeight, GRAY);
            game.HomePage();
            DrawTextEx(font, "FAST CAR", { 365, 15 }, 38, 2, WHITE);
            DrawRectangle(static_cast<int>(playButtonRect.x), static_cast<int>(playButtonRect.y), static_cast<int>(playButtonRect.width), static_cast<int>(playButtonRect.height),BLUE);
            DrawTextEx(font, "Play", { playButtonRect.x, playButtonRect.y }, 38, 2, RED);
            DrawRectangle(static_cast<int>(scoreButtonRect.x), static_cast<int>(scoreButtonRect.y), static_cast<int>(scoreButtonRect.width), static_cast<int>(scoreButtonRect.height), GREEN);
            DrawTextEx(font, "Score", { scoreButtonRect.x + 10, scoreButtonRect.y + 10 }, 38, 2, DARKGRAY);  // Ajustez les coordonnées pour centrer le texte
            DrawRectangle(static_cast<int>(settingsButtonRect.x), static_cast<int>(settingsButtonRect.y), static_cast<int>(settingsButtonRect.width), static_cast<int>(settingsButtonRect.height), DARKPURPLE);
            DrawTextEx(font, "Settings", { settingsButtonRect.x + 10, settingsButtonRect.y + 10 }, 38, 2, LIGHTGRAY);
            DrawText(TextFormat("Best Score: %d", game.bestScore), 10, 40, 30, WHITE);
        } break;
        case GAMEPLAY:
        {
            ClearBackground(GREEN);
            DrawRectangle(screenWidth / 4, 0, screenWidth / 2, screenHeight, GRAY);
            DrawText("Bouge ta caisse gros lard", 10, 10, 20, DARKGRAY);
            DrawText(TextFormat("Best Score: %d", game.bestScore), 10, 40, 30, WHITE);
            DrawText(TextFormat("Score: %d", game.score), screenWidth - 300, 10, 30, WHITE);  
            DrawTexture(COEURTexture, screenWidth - 215,40, WHITE);
            DrawText(TextFormat("%d", game.LIVE), screenWidth - 175, 55, 30, WHITE);
            DrawTexture(MenuBar, screenWidth - 90, 10, WHITE);
            Vector2 mousePos = GetMousePosition();
            if ((IsKeyDown(KEY_ESCAPE) || (CheckCollisionPointRec(mousePos, Menubar))) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                GameRun = false;
            }
            if (GameRun == false)
            {
                DrawRectangle(250, 30, 300, 350, WHITE);
                DrawRectangle(290, 100, 230, 55, BLACK);
                DrawText("RESUME", 300, 100, 50, DARKGRAY);
                DrawRectangle(295, 200, 230, 55, BLACK);
                DrawText("M E N U", 305, 200, 50, DARKGRAY);
            }

            if (GameRun==true)
            {
                game.Run();
            }
        } break;
        case ENDING:
        {
            DrawText("Game Over", screenWidth / 2 - 100, screenHeight / 2 - 50, 40, RED);
            DrawText("TAP ANY KEY TO TRY AGAIN", screenWidth / 2 - MeasureText("TAP ANY KEY TO TRY AGAIN", 20) / 2, screenHeight / 2 + 20, 20, GRAY);
        } break;
        default: break;
        }
        
        EndDrawing();
        
    }
    UnloadTexture(COEURTexture);
    UnloadTexture(MenuBar);
    CloseWindow();     
 
    return 0;
}