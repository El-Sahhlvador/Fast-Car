#pragma once
#include "raylib.h"

class Enemy
{
public:
    Enemy(Texture2D texture, Vector2 spawnPosition, float enemySpeed);
    Texture2D enemyTexture;
    Vector2 position;
    float speed;
    void Update();
    void Draw();
};