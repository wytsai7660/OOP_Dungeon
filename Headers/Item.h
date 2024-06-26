#ifndef ITEM
#define ITEM

#include <iostream>

#include "Object.h"

class Item : public Object {
public:
    Item();
    Item(std::string, const std::string, int);
    void setDescription(std::string _d);
    const std::string getDescription() const;
protected:
    int price;
    std::string description;
};

class Equipment : public Item {
public:
    Equipment();
    Equipment(std::string, int, int, int, int);
    int getHealth() const;
    int getAttack() const;
    int getDefense() const;
private:
    int health;
    int attack;
    int defense;
};

class Consumable : public Item {
public:
    Consumable();
    Consumable(std::string, int, int, int, int, int, bool);
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
