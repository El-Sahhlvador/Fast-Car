#include "enemy.h"
#include "Game.h"
#include <vector>
Enemy::Enemy(Texture2D texture, Vector2 spawnPosition, float enemySpeed)
    : enemyTexture(texture), position(spawnPosition), speed(enemySpeed)
{

}

void Enemy::Update()
{
    // Mettez à jour la position de l'ennemi ici, faites-les descendre
    position.y += speed;

}

void Enemy::Draw()
{
    // Dessinez l'ennemi à sa position actuelle
    DrawTexture(enemyTexture, (int)position.x, (int)position.y, WHITE);
}