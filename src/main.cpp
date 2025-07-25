#include <raylib.h>
#include "SpaceShip.h"
#include <vector>

const int winSizeX = {800};
const int windSizeY = {800};


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
    while(WindowShouldClose() == false)
    {
        Vector2 shipPosition = ship.getPosition();
        
        // Handle events
        if(IsKeyDown(KEY_RIGHT))
        {
            ship.updatePosition(shipPosition.x + 3.0, 0);
        }

        if(IsKeyPressed(KEY_SPACE))
        {
            PlaySound(sfxShoot);
        }

        //handle collision
       
        //draw
        ClearBackground(BLACK);
        BeginDrawing();

       

        DrawCircle(shipPosition.x,shipPosition.y,20, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}