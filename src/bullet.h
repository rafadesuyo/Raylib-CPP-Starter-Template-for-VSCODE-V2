#pragma once
#include <raylib.h>

class Bullet{
    public:
        Bullet(unsigned int damage);
        void UpdateBulletPos(Vector2 newPosition);
        const Vector2& GetBulletPosition();
    private:
        unsigned int Damage;
        Vector2 position = {0.5f,0.5f};
        Vector2 spawnPosition;
};