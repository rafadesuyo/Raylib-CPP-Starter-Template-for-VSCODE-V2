#pragma once
#include <raylib.h>

class Asteroid{
    public:
        Asteroid(unsigned int maxHealth);
        void takeDamage(unsigned int Amount);
        const Vector2& getPosition();
        void updatePosition(const Vector2& newPos);
    private:
        signed int health;
        unsigned int maxHealth;
        unsigned int currentHealth;
        Vector2 position = {400.0f,400.0f};
};