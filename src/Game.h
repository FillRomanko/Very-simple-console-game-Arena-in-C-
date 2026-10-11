#pragma once
#include "Fighter.h"
#include "MyMethods.h"

class Game {
public:
    static constexpr int EnemyCount = 3;

    Game();
    Game(const Fighter& player, const Fighter (&enemies)[EnemyCount]);

    static void PrintFighter(const Fighter& fighter);

    void Run();

private:
    Fighter player;
    Fighter enemies[EnemyCount];

    void ReorderEnemies();
    void PrintEnemies();
    int CountAlive();
};

