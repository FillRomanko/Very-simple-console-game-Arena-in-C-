#pragma once
#include "Fighter.h"
#include "MyMethods.h"

class Game {
public:
    static constexpr int EnemyCount = 3;

    Game();
    Game(const Fighter& player, const Fighter (&enemies)[EnemyCount]);

    void Run();

private:
    Fighter player;
    Fighter enemies[EnemyCount];

    static void PrintFighter(const Fighter& fighter);
    void PrintEnemies();
    int CountAlive();

    void ReorderEnemies();

    static void EndGame();
};

