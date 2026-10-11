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

void Game::ReorderEnemies() {
    int j = 0;
    for (int i = 0; i < EnemyCount; ++i) {
        if (enemies[i].IsAlive()) {
            if (i != j)
                std::swap(enemies[i], enemies[j]);
            ++j;
        }
    }
}

void Game::PrintEnemies() {
    int alive = 0;
    for (int i = 0; i < EnemyCount; ++i) {
        if (enemies[i].IsAlive()) {
            ++alive;
            std::cout << alive << ". " ;
            PrintFighter(enemies[i]);
            std::cout << '\n';
        }
    }
}

int Game::CountAlive() {
    int alive = 0;
    for (int i = 0; i < EnemyCount; ++i) {
        if (enemies[i].IsAlive()) ++alive;
    }
    return alive;
}

void Game::EndGame() {
    char exit = MyMethods::getChar("Input 0 to exit", "If you want to exit, input 0", "This stroke is too long for 0");
    while (exit != '0') {
        std::cout << "This is not 0" <<'\n';
        exit = MyMethods::getChar("Input 0 to exit", "If you want to exit, input 0", "This stroke is too long for 0");
    }
}
void Game::Run() {
    ReorderEnemies();
    while (true) {

        if (!player.IsAlive()) {
            std::cout << "You already die" << std::endl;
            break;
        }

        if (CountAlive() == 0) {
            std::cout << "You won!\n";
            break;
        };

        int alive = CountAlive();


        std::cout << "Player: ";
        PrintFighter(player);
        std::cout << '\n';
        PrintEnemies();
        std::cout << '\n';

        int target = MyMethods::getInt("Choose the target", "Try again to choose the target", "Your input is too big to be right number", "This is not number", "Your number is out of range for an int");
        while (target < 1 || target > alive) {
            std::cout << "You can't choose this target" <<'\n';
            PrintEnemies();
            target = MyMethods::getInt("Choose the target", "Try again to choose the target", "Your input is too big to be right number", "This is not number", "Your number is out of range for an int");
        }
        --target;
        player.Attack(enemies[target]);

        if (enemies[target].IsAlive()) {
            std::cout << "enemy attacks you!" << std::endl;
            enemies[target].Attack(player);
            if (!player.IsAlive()) {
                std::cout << "You die!" << std::endl;
                break;
            }
        }
    }
    EndGame();
}
