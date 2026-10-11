#include "Game.h"

Game::Game():player("Hero", 30, 8),
enemies{{"Enemy 1", 12, 3},
    {"Enemy 2", 18, 4},
    {"Enemy 3", 24, 5}} {}

Game::Game(const Fighter& player, const Fighter (&enemies)[3])
: player(player), enemies{enemies[0], enemies[1], enemies[2]} {}

void Game::PrintFighter(const Fighter& fighter) {
    fighter.PrintStatus();
}

void Game::Run() {
    while (true) {
        if (!player.IsAlive()) {
            std::cout << "You already die" << std::endl;
            return;
        }
        int alive = 0;
        std::cout << "Player: ";
        player.PrintStatus();
        std::cout << std::endl;
        if (enemies[0].IsAlive()) {
            alive++;
            std::cout << alive << ". "<<std::endl;
            PrintFighter(enemies[0]);
        }
        if (enemies[1].IsAlive()) {
            alive++;
            std::cout << alive << ". "<<std::endl;
            PrintFighter(enemies[1]);
        }
        if (enemies[2].IsAlive()) {
            alive++;
            std::cout << alive << ". "<<std::endl;
            PrintFighter(enemies[2]);
        }

        if (alive == 0) {
            std::cout << "You won!" << std::endl;
            return;
        }
        std::cout << std::endl;
        std::cout << "Choose target" << std::endl;

        char buf[100];
        while (std::cin >> buf && (buf[0] < '1' || buf[0] > '0' + alive)) {
            std::cout << "Choose another target" << std::endl;
        }
        int pol = buf[0] - '0' - 1;
        player.Attack(enemies[pol]);

        if (enemies[pol].IsAlive()) {
            std::cout << "enemy attacks you!" << std::endl;
            enemies[pol].Attack(player);
            if (!player.IsAlive()) {
                std::cout << "You die!" << std::endl;
                return;
            }
        }
    }
}

