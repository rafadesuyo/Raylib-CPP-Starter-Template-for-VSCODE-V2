#pragma once
class Bullet{
    public:
        Bullet(unsigned int damage);
        void UpdateBulletPos(int posX, int posY);
    private:
        unsigned int Damage;
        int posX;
        int posY;
};