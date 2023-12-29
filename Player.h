#pragma once
#include "raylib.h"
#include "enemy.h"

class Player
{
public:
    Texture2D playerTexture;
    Vector2 position;
    int lives;

    Player(Texture2D texture, Vector2 spawnPosition, int startingLives);
    void Update();
    void Draw();
    bool CheckCollision(Enemy enemy);
    void Destroy();
};
