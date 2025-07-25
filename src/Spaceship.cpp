#include "SpaceShip.h"
#include "bullet.h"
#include <vector>

SpaceShip::SpaceShip(unsigned int damage, unsigned int maxHealth)
    : damage(damage), maxHealth(maxHealth), currentHealth(maxHealth)
{}

unsigned int SpaceShip::getDamage() const {
    return damage;
}

void SpaceShip::setDamage(unsigned int newDamage){
    damage = newDamage;
}

void SpaceShip::takeDamage(unsigned int Amount) {
    currentHealth -= Amount;
}

Vector2 SpaceShip::getPosition()
{
    return position;
}

void SpaceShip::updatePosition(float newX, float newY)
{
    position.x = newX;
    position.y = newY;
}

