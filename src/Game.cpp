#include "Game.h"

Game::Game():player("Hero", 20, 8),
enemies{{"Enemy 1", 12, 3},
    {"Enemy 2", 18, 4},
    {"Enemy 3", 24, 5}} {}

Game::Game(const Fighter& player, const Fighter (&enemies)[EnemyCount])
: player(player), enemies{enemies[0], enemies[1], enemies[2]} {}

void Game::PrintFighter(const Fighter& fighter){
    fighter.PrintStatus();
}

void Game::PrintEnemies() const{
    for (int i = 0; i < EnemyCount; ++i) {
        std::cout << i + 1 << ". " ;
        PrintFighter(enemies[i]);
        std::cout << '\n';
    }
}


int Game::CountAlive() const {
    int alive = 0;
    for (int i = 0; i < EnemyCount; ++i) {
        if (enemies[i].IsAlive()) ++alive;
    }
    return alive;
}
bool Game::AllEnemiesDefeated() const {
    return CountAlive() == 0;
}

bool Game::TrySelectTarget(int number, Fighter*& outTarget) {
    outTarget = nullptr;
    if (number < 1 || number > EnemyCount) return false;
    if (!enemies[number - 1].IsAlive()) return false;
    outTarget = &enemies[number - 1];
    return true;
}

void Game::Run() {
    while (true) {
        if (!player.IsAlive()) {
            std::cout << "You die!\n";
            return;
        }

        if (AllEnemiesDefeated()) {
            std::cout << "You won!\n";
            return;
        }

        std::cout << "Player: ";
        PrintFighter(player);
        std::cout << " : " << medkits <<" medkits\n";
        std::cout << '\n';
        if (currentTarget) {
            std::cout << "Target: ";
            PrintFighter(*currentTarget);
            std::cout << '\n';
        } else {
            std::cout << "Target: none\n";
        }
        std::cout << '\n';
        PrintEnemies();
        std::cout << '\n';
        int input;
        if (!MyMethods::getIntOnce("Input 1 to choose target\nInput 2 to attack the target\nInput 3 to use heal\nInput 0 to exit", input)) {
            break;
        }

        if (input == 1) {
            // int alive = CountAlive(); // it could be playable...
            currentTarget = nullptr;
            PrintEnemies();

            int target;
            if (!MyMethods::getIntOnce("Choose the target", target)) {break;}

            if (TrySelectTarget(target, currentTarget)) {
                std::cout << "You choose ";
                PrintFighter(*currentTarget);
                std::cout << "\n\n";
            } else {
                std::cout << "Invalid target\n";
            }
        }

        if (input == 2) {
            if (!currentTarget || !currentTarget->IsAlive()) {
                currentTarget = nullptr;
                std::cout << "Choose alive target\n";
                continue;
            }
            std::cout << "You attack " ;
            PrintFighter(*currentTarget);
            player.Attack(*currentTarget);
            std::cout << '\n' << "Now ";
            PrintFighter(*currentTarget);
            std::cout << '\n';

            if (currentTarget->IsAlive()) {
                PrintFighter(*currentTarget);
                std::cout << " attacks you!\n";
                std::cout << '\n';
                currentTarget->Attack(player);
                if (!player.IsAlive()) {
                    continue;
                }
            }
            else {
                currentTarget = nullptr;
                continue;
            }
        }
        if (input == 3) {
            if (!currentTarget || !currentTarget->IsAlive()) {
                currentTarget = nullptr;
                std::cout << "Choose alive target\n";
                continue;
            }
            else {
                if (medkits < 1) {
                    std::cout << "You must have medkit\n";
                    continue;
                }
                std::cout << "you use medkit\n";
                player.Heal(medkitsPower);
                --medkits;
                std::cout << "now Player: ";
                PrintFighter(player);
                std::cout << " : " << medkits <<" medkits\n";
                std::cout << '\n';

                PrintFighter(*currentTarget);
                std::cout << " attacks you!\n";
                currentTarget->Attack(player);
            }
        }

        if (input == 0) {return;}
    }
}