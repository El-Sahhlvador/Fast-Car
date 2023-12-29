#pragma once
#include "raylib.h"
#include "player.h"
#include "enemy.h"
#include <vector>

class Game
{
public:
    Game(int screenWidth, int screenHeight);
    ~Game();

    void Run();
    void HomePage();
    void GenerateEnemies();
    void GenerateTrees();
    bool IsEnemyTexture(Texture2D texture);
    void CheckCollisions();
    int score;
    int LIVE;
    double lastUpdateTime;
    void UpdateScore();
    bool GameOver;
    void Reset();
    int getBestScore();
    int bestScore;
    void updateBestScore(int currentScore);
    Music music;
    Sound CarPassingBy;
    Sound Drift;
    Sound TAHLAMORT;
    Sound TASPERDUUNEVIECHEFMAISTASDELACHANCETENAS3;
    void ClearEntities();

private:
    int screenWidth;
    int screenHeight;
    Texture2D carTexture;
    Vector2 carPosition;
    Player player;
    std::vector<Texture2D> enemyTextures;
    std::vector<Texture2D> treeTextures;
    std::vector<Enemy> enemies;
    bool TahLeGameplay;

};