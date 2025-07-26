#include "SpaceShip.h"
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

const Vector2& SpaceShip::getPosition()
{
    return position;
}

void SpaceShip::updatePosition(const Vector2& newPos)
{
    position = newPos;
}

const Vector2& SpaceShip::getBulletSpawnPosition()
{
    return bulletSpawnPosition;
}

