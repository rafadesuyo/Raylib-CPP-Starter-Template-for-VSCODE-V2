#pragma once
#include <raylib.h>
#include <vector>


class SpaceShip {
public:
    SpaceShip(unsigned int damage, unsigned int maxHealth);
    unsigned int getDamage() const;
    void takeDamage(unsigned int Amount);
    void setDamage(unsigned int newDamage);
    Vector2 getPosition();
    void updatePosition(float newX, float newY);

private:
    unsigned int damage;
    unsigned int maxHealth;
    unsigned int currentHealth;
    Vector2 position = {0.0f,0.0f};
};
