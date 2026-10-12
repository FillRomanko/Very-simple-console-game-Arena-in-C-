#include <iostream>

void ClearBadInput() {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

bool getIntOnce(const char* request, int& res) {
    static constexpr int int_buf_size = 13;
    char buf[int_buf_size];

    std::cout << request << '\n';
    std::cin.getline(buf, int_buf_size);

    if (std::cin.fail()) {
        ClearBadInput();
        return false;
    }

    int i = 0;
    bool neg = false;
    if (buf[0] == '-') { neg = true; i = 1; }

    if (buf[i] == '\0') {
        return false;
    }

    bool ok = true;
    for (int j = i; buf[j] != '\0'; ++j) {
        if (buf[j] < '0' || buf[j] > '9') { ok = false; break; }
    }
    if (!ok) {
        return false;;
    }

    long val = 0;
    const long long limit = neg ? 2147483647LL  + 1 : 2147483647LL;
    for (; buf[i] != '\0'; ++i) {
        if (val >  (limit - (buf[i] - '0')) / 10) { ok = false; break; }
        val = val * 10 + (buf[i] - '0');
    }
    if (!ok) {
        return false;
    }

    res =  neg ? (int)(-val) : (int)val;
    return true;
}

class Fighter {
public:
    Fighter(const char* name, int health, int maxHealth, int damage)
        : name(name), health(health), maxHealth(maxHealth), damage(damage) {}

    Fighter(const char* name, int health, int damage)
        : name(name), health(health), maxHealth(health), damage(damage) {}

    void TakeDamage(int amount) {
        if (amount < 0) return;
        health = health > amount ? health - amount : 0;
    }

    void Heal(int amount) {
        if (amount < 0) return;
        health = maxHealth - amount <= health ? maxHealth : health + amount;
    }

    void Attack(Fighter& target) const {
        target.TakeDamage(damage);
    }

    [[nodiscard]] bool IsAlive() const {
        return health > 0;
    }

    void PrintStatus() const {
        std::cout << name << " : " << health << "HP";
    }
private:
    const char* name;
    int health;
    int maxHealth;
    int damage;
};

class Game {
public:
    static constexpr int EnemyCount = 3;
    Game():player("Hero", 20, 8),
enemies{{"Enemy 1", 12, 3},
    {"Enemy 2", 18, 4},
    {"Enemy 3", 24, 5}} {}

    Game(const Fighter& player, const Fighter (&enemies)[EnemyCount])
    : player(player), enemies{enemies[0], enemies[1], enemies[2]} {}

    static void PrintFighter(const Fighter& fighter){
        fighter.PrintStatus();
    }

    void PrintEnemies() const{
        for (int i = 0; i < EnemyCount; ++i) {
            std::cout << i + 1 << ". " ;
            PrintFighter(enemies[i]);
            std::cout << '\n';
        }
    }


    [[nodiscard]] int CountAlive() const {
        int alive = 0;
        for (int i = 0; i < EnemyCount; ++i) {
            if (enemies[i].IsAlive()) ++alive;
        }
        return alive;
    }
    [[nodiscard]] bool AllEnemiesDefeated() const {
        return CountAlive() == 0;
    }

    bool TrySelectTarget(int number, Fighter*& outTarget) {
        outTarget = nullptr;
        if (number < 1 || number > EnemyCount) return false;
        if (!enemies[number - 1].IsAlive()) return false;
        outTarget = &enemies[number - 1];
        return true;
    }

    void Run() {
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
            if (!getIntOnce("Input 1 to choose target\nInput 2 to attack the target\nInput 3 to use heal\nInput 0 to exit", input)) {
                break;
            }

            if (input == 1) {
                // int alive = CountAlive(); // it could be playable...
                currentTarget = nullptr;
                PrintEnemies();

                int target;
                if (!getIntOnce("Choose the target", target)) {break;}

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
private:
    Fighter player;
    Fighter enemies[EnemyCount];

    Fighter* currentTarget = nullptr;

    int medkits = 1;
    int medkitsPower = 8;
};



int main() {
    Game game = Game();
    game.Run();
    return 0;
}