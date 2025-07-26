#include "bullet.h"
#include <raylib.h>

Bullet::Bullet(unsigned int Damage,Vector2 spawnPosition)
    : Damage(Damage), spawnPosition(spawnPosition)
{}

void Bullet::UpdateBulletPos(Vector2 newPosition){
    position = newPosition;
}

const Vector2& Bullet::GetBulletPosition(){
    return position;
}
