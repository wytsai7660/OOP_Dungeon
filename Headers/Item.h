#ifndef Item
#define Item

#include <iostream>

#include "Object.h"

class Equipment : public Object {
public:
    Equipment();
    Equipment(std::string, int, int, int);
    const int getHealth() const;
    const int getAttack() const;
    const int getDefense() const;
private:
    int health;
    int attack;
    int defense;
};

class Consumable : public Object {
public:
    Consumable();
    Consumable(std::string, int, int, int, int, bool);
    const int getHealth() const;
    const int getHunger() const;
    const int getThirsty() const;
    const int getPoisonous() const;
    const bool isAntinode() const;
private:
    int health;
    int hunger;
    int thirsty;
    int poisonous;
    bool antinode;
};
#endif