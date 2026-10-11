#include <algorithm>
#include <iostream>


class Fighter {
    public:

    Fighter(const char* name, int maxHealth, int health, int damage)
    : name(name), health(health), maxHealth(maxHealth), damage(damage) {}

    Fighter(const char* name, int maxHealth, int damage)
    : name(name), maxHealth(maxHealth), damage(damage), health(maxHealth) {}

    void TakeDamage(int amount) {health = health > amount ? health - amount : 0;}

    void Attack(Fighter& target) const {target.TakeDamage(damage);}

    bool IsAlive() const {return health > 0;}

    void PrintStatus() const {std::cout << name << ": " << health;}

    private:

    const char* name;
    int health;
    int maxHealth;
    int damage;
};

class Game {
    public:

    Game() : player("Hero", 30, 8),
    enemies{{"Enemy 1", 12, 3},
        {"Enemy 2", 18, 4},
        {"Enemy 3", 24, 5}} {}

    Game(const Fighter& player, const Fighter (&enemies)[3])
    : player(player), enemies{enemies[0], enemies[1], enemies[2]} {}

    void Run() {
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

    void PrintFighter(const Fighter& fighter) {
        fighter.PrintStatus();
    }

    private:
    Fighter enemies[3];
    Fighter player;
};

int main() {
    Game game = Game(
        Fighter("Hero", 30, 8),
        {Fighter("Enemy", 12, 3), Fighter("", 0, 0), Fighter("", 0, 0)}
        );
    game.Run();
}