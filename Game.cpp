#include "game.h"
#include <fstream>
#include <iostream>
using namespace std;

Game::Game(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight), carTexture(LoadTexture("Skin/car.png")),
    carPosition{ (float)(screenWidth / 2 - carTexture.width / 2), (float)(screenHeight - carTexture.height - 50) },
    player(carTexture, carPosition, 3)
{
    enemyTextures.push_back(LoadTexture("Skin/Enemie/car1.png"));
    enemyTextures.push_back(LoadTexture("Skin/Enemie/car2.png"));
    enemyTextures.push_back(LoadTexture("Skin/Enemie/car3.png"));
    enemyTextures.push_back(LoadTexture("Skin/Enemie/car4.png"));
    enemyTextures.push_back(LoadTexture("Skin/Enemie/car5.png"));
    enemyTextures.push_back(LoadTexture("Skin/Enemie/car6.png"));

    treeTextures.push_back(LoadTexture("Skin/Trees/tree1.png"));
    treeTextures.push_back(LoadTexture("Skin/Trees/tree2.png"));
    treeTextures.push_back(LoadTexture("Skin/Trees/tree3.png"));
    treeTextures.push_back(LoadTexture("Skin/Trees/tree4.png"));
    treeTextures.push_back(LoadTexture("Skin/Trees/tree5.png"));
    treeTextures.push_back(LoadTexture("Skin/Trees/tree6.png"));
    treeTextures.push_back(LoadTexture("Skin/Trees/tree7.png"));
    treeTextures.push_back(LoadTexture("Skin/Trees/tree8.png"));
    treeTextures.push_back(LoadTexture("Skin/Trees/tree9.png"));

    
    score = 0;
    lastUpdateTime = 0;
    GameOver = false;
    LIVE = 0;
    bestScore = 0;
    TahLeGameplay = false;
    InitAudioDevice();
    music = LoadMusicStream("Sounds/MusicDuFond.mp3");
    PlayMusicStream(music);
    CarPassingBy = LoadSound("Sounds/CarPassingBy.mp3");
    Drift = LoadSound("Sounds/Drift.mp3");
    TAHLAMORT = LoadSound("Sounds/GameOver.mp3");
    TASPERDUUNEVIECHEFMAISTASDELACHANCETENAS3 = LoadSound("Sounds/Explosion.mp3");

}




Game::~Game()
{
    UnloadSound(TASPERDUUNEVIECHEFMAISTASDELACHANCETENAS3);
    UnloadSound(TAHLAMORT);
    UnloadSound(CarPassingBy);
    UnloadSound(Drift);
    UnloadMusicStream(music);
    CloseAudioDevice();
    UnloadTexture(carTexture);
    

    for (const Texture2D& texture : enemyTextures)
    {
        UnloadTexture(texture);
    }
    for (const Texture2D& texture : treeTextures)
    {
        UnloadTexture(texture);
    }
}

void Game::GenerateEnemies()
{
    //////// Générez aléatoirement de nouveaux ennemis
    if (GetRandomValue(0, 100) < 5)
    {
        Texture2D randomTexture = enemyTextures[GetRandomValue(0, enemyTextures.size() - 1)];
        Vector2 spawnPosition = { (float)GetRandomValue(screenWidth / 4, screenWidth / 4 * 3 - randomTexture.width), (float)-randomTexture.height };
        float enemySpeed = (float)GetRandomValue(2, 5);
        enemies.push_back(Enemy(randomTexture, spawnPosition, enemySpeed));
    }
}

void Game::GenerateTrees()
{
    if (GetRandomValue(0, 100) < 5)
    {
        Texture2D randomTexture = treeTextures[GetRandomValue(0, treeTextures.size() - 1)];
        Vector2 spawnPosition = { (float)GetRandomValue(0, screenWidth / 4 - randomTexture.width), 0 };
        float enemySpeed = 3;
        enemies.push_back(Enemy(randomTexture, spawnPosition, enemySpeed));
    }
    if (GetRandomValue(0, 100) < 5)
    {
        Texture2D randomTexture = treeTextures[GetRandomValue(0, treeTextures.size() - 1)];
        Vector2 spawnPosition = { (float)GetRandomValue(screenWidth / 4 * 3, screenWidth - randomTexture.width), 0 };
        float enemySpeed = 3;
        enemies.push_back(Enemy(randomTexture, spawnPosition, enemySpeed));
    }
}

bool Game::IsEnemyTexture(Texture2D texture)
{
    for (const auto& enemyTexture : enemyTextures)
    {
        
        if (enemyTexture.id == texture.id)
        {
            return true;
        }
    }

    return false;
}

void Game::CheckCollisions()
{
    // Gestion des collisions
    std::vector<Enemy> validEnemies;

    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i].Update();
        if (enemies[i].position.y == (float)(screenHeight - carTexture.height - 50))
        {
            if (TahLeGameplay == false)
            {
            
                PlaySound(CarPassingBy);
            }
        }

        // Vérifiez si l'ennemi a dépassé la hauteur de l'écran
        if (enemies[i].position.y < GetScreenHeight())
        {
            // Ajoutez l'ennemi au vecteur temporaire
            validEnemies.push_back(enemies[i]);
        }
        else
        {
            // Vérifiez si la texture est celle d'un ennemi avant d'ajouter des points
            if (IsEnemyTexture(enemies[i].enemyTexture))
            {
                if (TahLeGameplay == false)
                {
                    // Ajoutez +2 au score pour chaque ennemi qui a dépassé la hauteur de l'écran
                    score += 2;
                }
            }
        }
        LIVE = player.lives;
        if (player.CheckCollision(enemies[i]))
        {
            player.lives--;
            PlaySound(TASPERDUUNEVIECHEFMAISTASDELACHANCETENAS3);
            if (player.lives <= 0)
            {
                updateBestScore(score);
                GameOver = true;
                PlaySound(TAHLAMORT);
            }
            else
            {
                // Réinitialisez la position du joueur
                player.position = carPosition;
            }
        }
        if (IsKeyDown(KEY_RIGHT)) PlaySound(Drift);

        if (IsKeyDown(KEY_LEFT)) PlaySound(Drift);
    }

    // Remplacez le vecteur d'ennemis par le vecteur temporaire
    enemies = validEnemies;
}

void Game::UpdateScore()
{
    double currentTime = GetTime();

    if (currentTime - lastUpdateTime >= 0.25) // Si une seconde s'est écoulée depuis la dernière mise à jour
    {
        score += 1; // Ajoutez 3 points au score
        lastUpdateTime = currentTime; // Mettez à jour le temps de la dernière mise à jour
    }
}

void Game::Reset()
{
    score = 0;
    ClearEntities();
    player.lives = 3;
    GameOver = false;
}

int Game::getBestScore() {
    ifstream file("bestscore.txt");
    if (file.is_open()) {
        file >> bestScore;
        file.close();
    }
    return bestScore;
}

void Game::updateBestScore(int currentScore) {
    int bestScore = getBestScore();
    if (currentScore > bestScore) {
        ofstream file("bestscore.txt");
        if (file.is_open()) {
            file << currentScore;
            file.close();
        }
    }
}

void Game::ClearEntities()
{
    enemies.clear();
}


void Game::Run()
{

    TahLeGameplay = false;
    updateBestScore(score);
    GenerateEnemies();
    GenerateTrees();
    player.Update();
    CheckCollisions();
    UpdateScore();

    player.Draw();

    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i].Draw();
    }
}

void Game::HomePage()
{
    TahLeGameplay = true;
    GenerateEnemies();
    GenerateTrees();
    CheckCollisions();
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i].Draw();
    }
}




