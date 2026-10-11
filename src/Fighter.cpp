#include "Fighter.h"
#include <iostream>

Fighter::Fighter(const char* name, int maxHealth, int health, int damage)
    : name(name), health(health), maxHealth(maxHealth), damage(damage) {}

Fighter::Fighter(const char* name, int maxHealth, int damage)
    : name(name), maxHealth(maxHealth), damage(damage), health(maxHealth) {}

void Fighter::TakeDamage(int amount) {
    health = health > amount ? health - amount : 0;
}

void Fighter::Attack(Fighter& target) const {
    target.TakeDamage(damage);
}

bool Fighter::IsAlive() const {
    return health > 0;
}

void Fighter::PrintStatus() const {
    std::cout << name << ": " << health;
}