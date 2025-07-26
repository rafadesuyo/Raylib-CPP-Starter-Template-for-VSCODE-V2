#pragma once
#include <raylib.h>

class Bullet{
    public:
        Bullet(unsigned int damage, Vector2 spawnPosition);
        void UpdateBulletPos(Vector2 newPosition);
        const Vector2& GetBulletPosition();
    private:
        unsigned int Damage;
        Vector2 position;
        Vector2 spawnPosition;
};