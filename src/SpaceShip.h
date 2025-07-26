#pragma once
#include <raylib.h>
#include <vector>

class SpaceShip {
public:
    SpaceShip(unsigned int damage, unsigned int maxHealth);
    unsigned int getDamage() const;
    void takeDamage(unsigned int Amount);
    void setDamage(unsigned int newDamage);
    const Vector2& getPosition();
    const Vector2& getBulletSpawnPosition();
    void updatePosition(const Vector2& newPos);

private:
    unsigned int damage;
    unsigned int maxHealth;
    unsigned int currentHealth;
    Vector2 position = {0.5f,0.5f};
    Vector2 bulletSpawnPosition = {0.5f,0.5f};
};
