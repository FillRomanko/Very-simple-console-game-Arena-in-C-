#pragma once
#include <iostream>

class Fighter {
public:

    Fighter(const char* name, int maxHealth, int health, int damage);
    Fighter(const char* name, int maxHealth, int damage);
    void TakeDamage(int amount);
    void Attack(Fighter& target) const;
    bool IsAlive() const;
    void PrintStatus() const;

private:
    const char* name;
    int health;
    int maxHealth;
    int damage;
};

