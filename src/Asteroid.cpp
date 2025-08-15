#include "asteroid.h"

Asteroid::Asteroid(unsigned int maxHealth)
    : maxHealth(maxHealth), currentHealth(maxHealth)
{}

void Asteroid::updateAsteroidPosition(const Vector2& newPosition) {
    position = newPosition;
    collisionBox.x = newPosition.x;
    collisionBox.y = newPosition.y;
}

const Vector2& Asteroid::GetPosition() {
    return position;
}

const Rectangle& Asteroid::GetCollisionBox(){
    return collisionBox;
}
