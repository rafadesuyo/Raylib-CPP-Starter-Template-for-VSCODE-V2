#pragma once
#include <raylib.h>

class Asteroid {
public:
    Asteroid(unsigned int maxHealth);
    void takeDamage(unsigned int amount);
    const Vector2& GetPosition();
    void updateAsteroidPosition(const Vector2& newPosition);
    float speed = 1.0f;
    float rotation;
    Vector2 direction;
    const Rectangle& GetCollisionBox();
private:
    unsigned int maxHealth;
    unsigned int currentHealth;
    Vector2 position = {400.0f, 400.0f};
    Rectangle collisionBox = { position.x, position.y, 10, 10 }; 
};
