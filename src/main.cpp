#include <raylib.h>
#include "SpaceShip.h"
#include <vector>
#include "Bullet.h"
#include <cstddef>
#include <memory>

const int winSizeX = 800;
const int windSizeY = 800;


int main()
{
    SpaceShip ship(10,20);
    ship.setDamage(1500);

    InitWindow(winSizeX,windSizeY, "Window");
    InitAudioDevice();
    SetTargetFPS(60);

    //Audio
    Sound sfxShoot = LoadSound("resources/shoot.wav");
    //Sound sfxHitTarget = LoadSound("resources/shoot.wav");
    //Sound sfxDie = LoadSound("resources/shoot.wav");

    //Game loop

    //Pool of objects
    std::vector<std::unique_ptr<Bullet>> bulletList;

    while(WindowShouldClose() == false)
    {
        Vector2 shipPosition = ship.getPosition();
        
        // Handle events
        if(IsKeyDown(KEY_RIGHT))
        {
            shipPosition.x += 3.0;
            ship.updatePosition(shipPosition);
        }

        if(IsKeyDown(KEY_LEFT))
        {
            shipPosition.x -= 3.0;
            ship.updatePosition(shipPosition);
        }

        if(IsKeyDown(KEY_UP))
        {
            shipPosition.y -= 3.0;
            ship.updatePosition(shipPosition);
        }

        if(IsKeyDown(KEY_DOWN))
        {
            shipPosition.y += 3.0;
            ship.updatePosition(shipPosition);
        }


        //Spawn a bullet
        if(IsKeyPressed(KEY_SPACE))
        {
            bulletList.push_back(std::make_unique<Bullet>(1,ship.getBulletSpawnPosition()));
            PlaySound(sfxShoot);
        }

        //handle collision
       
        //draw
        
        BeginDrawing();
        ClearBackground(BLACK);

        //Drawing bullets
        for (const auto& bullet : bulletList)
             DrawCircle(bullet->GetBulletPosition().x, bullet->GetBulletPosition().y, 20, PURPLE);

        DrawCircle(shipPosition.x,shipPosition.y,20, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}