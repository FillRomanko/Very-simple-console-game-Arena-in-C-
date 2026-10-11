#pragma once
#include "Fighter.h"
#include "MyMethods.h"

class Game {
public:
    static constexpr int EnemyCount = 3;

    Game();
    Game(const Fighter& player, const Fighter (&enemies)[EnemyCount]);
    void Run();
    static void PrintFighter(const Fighter& fighter);
    void ReorderEnemies();
    void PrintEnemies();
    int CountAlive();

private:
    Fighter player;
    Fighter enemies[EnemyCount];
};

