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

    Fighter* currentTarget = nullptr;

    int medkits = 1;
    int medkitsPower = 8;

    static void PrintFighter(const Fighter& fighter);
    void PrintAliveEnemies() const;

    void PrintEnemies() const;

    bool AllEnemiesDefeated() const;

    int CountAlive() const;

    bool TrySelectTarget(int number, Fighter*& outTarget);

    void ReorderEnemies();
};

