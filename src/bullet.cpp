#include "bullet.h"
#include <raylib.h>

Bullet::Bullet(unsigned int Damage)
    : Damage(Damage)
{}

void Bullet::UpdateBulletPos(Vector2 newPosition){
    position = newPosition;
}

void Bullet::UpdateCollisionRectanglePos(Vector2 newPosition){
    collisionBox.x = newPosition.x;
    collisionBox.y = newPosition.y;
}

const Vector2& Bullet::GetBulletPosition(){
    return position;
}

const Rectangle& Bullet::GetBulletCollisionRectangle(){
    return collisionBox;
}
