#include "player.h"

Player::Player(Texture2D texture, Vector2 spawnPosition, int startingLives)
    : playerTexture(texture), position(spawnPosition), lives(startingLives)
{
}

void Player::Update()
{
    // Mise à jour de la position du joueur
    if (IsKeyDown(KEY_RIGHT))position.x += 2.0f;

    if (IsKeyDown(KEY_LEFT)) position.x -= 2.0f;
}

void Player::Draw()
{
    // Dessinez le joueur à sa position actuelle
    DrawTexture(playerTexture, (int)position.x, (int)position.y, WHITE);
}

bool Player::CheckCollision(Enemy enemy)
{
    Rectangle playerRect = { position.x, position.y, (float)playerTexture.width, (float)playerTexture.height };
    Rectangle enemyRect = { enemy.position.x, enemy.position.y, (float)enemy.enemyTexture.width, (float)enemy.enemyTexture.height };

    return CheckCollisionRecs(playerRect, enemyRect);
}

void Player::Destroy()
{
    position = { 0, 0 };
    lives--;
}