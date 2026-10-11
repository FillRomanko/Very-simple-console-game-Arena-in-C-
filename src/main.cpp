#include <iostream>
#include "Game.h"

int main() {
    Game game = Game(
        Fighter("Hero", 30, 8),
        {Fighter("Enemy", 12, 3), Fighter("", 0, 0), Fighter("", 0, 0)}
        );
    game.Run();
}