#include "bullet.h"
Bullet::Bullet(unsigned int Damage)
    : Damage(Damage)
{}

void Bullet::UpdateBulletPos(int newPosX, int newPosY){
    posX = newPosX;
    posY = newPosY;
}
