#pragma once
#include "Fighter.h"

class Game {
public:
    Game();
    Game(const Fighter& player, const Fighter (&enemies)[3]);
    void Run();
    static void PrintFighter(const Fighter& fighter);

private:
    Fighter player;
    Fighter enemies[3];
};

