#include <raylib.h>
#include "SpaceShip.h"
#include <vector>
#include "Bullet.h"
#include <cstddef>
#include <memory>
#include <map>
#include "raymath.h"

const int winSizeX = 800;
const int windSizeY = 800;

const std::map<int,Bullet> PrewarmBulletPool()
{
    std::map<int,Bullet> pool;

    for(int i = 0; i < 30; ++i)
    {
        //Bullet bullet (1);
        //pool[i] = bullet;
    }
    return pool;
}


int main()
{
    //Player ship
    SpaceShip ship(10,20);
    float rotationAngle = 90.0;
    ship.setDamage(1500);
    Vector2 shipPosition = ship.getPosition();

    //Bullets
    //std::map<int,Bullet> bulletPool = PrewarmBulletPool();
   
    InitWindow(winSizeX,windSizeY, "Window");
    InitAudioDevice();
    SetTargetFPS(60);

    //Sprites
    Texture2D spaceShipSprite = LoadTexture("resources/Spaceship.png");
    Vector2 origin = { spaceShipSprite.width / 2.0f, spaceShipSprite.height / 2.0f };

    //Audio
    Sound sfxShoot = LoadSound("resources/shoot.wav");
    //Sound sfxHitTarget = LoadSound("resources/shoot.wav");
    //Sound sfxDie = LoadSound("resources/shoot.wav");

    //Game loop
    while(WindowShouldClose() == false)
    {
        float movementSpeed = 100.0f * GetFrameTime();

       Vector2 direction = { //-90 is the rotation of the sprite
            cosf((rotationAngle - 90.0f) * DEG2RAD),
            sinf((rotationAngle - 90.0f) * DEG2RAD)
        };

        // Handle events
        if(IsKeyDown(KEY_RIGHT))
        {
            rotationAngle += 3.0;
        }

        if(IsKeyDown(KEY_LEFT))
        {
            rotationAngle -= 3.0;
        }

        if(IsKeyDown(KEY_UP))
        {
            shipPosition.x += direction.x * movementSpeed;
            shipPosition.y += direction.y * movementSpeed;
            //ship.updatePosition(shipPosition);
        }

        if(IsKeyDown(KEY_DOWN))
        {
            shipPosition.x += direction.x * movementSpeed;
            shipPosition.y += direction.y * movementSpeed;
            //ship.updatePosition(shipPosition);
        }


        //Spawn a bullet
        if(IsKeyPressed(KEY_SPACE))
        {
            PlaySound(sfxShoot);
        }

        //handle collision
       
        //draw
        
        BeginDrawing();
        ClearBackground(BLACK);

        //Drawing bullets

        DrawTexturePro(
                spaceShipSprite,Rectangle{ 0, 0, (float)spaceShipSprite.width, (float)spaceShipSprite.height },
                Rectangle{ shipPosition.x, shipPosition.y, (float)spaceShipSprite.width, (float)spaceShipSprite.height },
                origin,
                rotationAngle,
                WHITE
            );

        EndDrawing();
    }

    CloseWindow();
    return 0;
}