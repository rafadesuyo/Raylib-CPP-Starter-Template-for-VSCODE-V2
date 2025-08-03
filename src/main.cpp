#include <raylib.h>
#include "SpaceShip.h"
#include <vector>
#include "Bullet.h"
#include <cstddef>
#include <memory>
#include <map>
#include "raymath.h"
#include <queue>

// Window
const int winSizeX = 800;
const int windSizeY = 800;

// Boundaries
const Rectangle rightRectangle = { winSizeX -50, 0, 50.0,windSizeY};
const Rectangle leftRectangle = {0, 0, 50.0,windSizeY};
const Rectangle topRectangle = {0, 0, winSizeX,50};
const Rectangle bottomRectangle = {0, windSizeY - 50, winSizeX,50};

const std::queue<Bullet> PrewarmBulletPool()
{
    std::queue<Bullet> bulletPool;

    for(int i = 0; i < 5; ++i)
    {
        bulletPool.push(Bullet(1));
    }
    return bulletPool;
}

int main()
{
    //Player ship
    SpaceShip ship(10,20);
    float rotationAngle = 90.0;
    ship.setDamage(1500);
    Vector2 shipPosition = ship.getPosition();

    //Bullets queue
    std::queue<Bullet> bulletPool = PrewarmBulletPool();
    std::vector<Bullet> activeBullets;

    InitWindow(winSizeX,windSizeY, "Window");
    InitAudioDevice();
    SetTargetFPS(60);

    //Loading Sprites
    Texture2D spaceShipSprite = LoadTexture("resources/Spaceship.png");
    Texture2D bulletSprite = LoadTexture("resources/bullet.png");

    Vector2 anchorPoint = { spaceShipSprite.width / 2.0f, spaceShipSprite.height / 2.0f }; //origin in the center is equals to half of the size of it

    //Audio
    Sound sfxShoot = LoadSound("resources/shoot.wav");
    //Sound sfxHitTarget = LoadSound("resources/shoot.wav");
    //Sound sfxDie = LoadSound("resources/shoot.wav");

    //Game loop
    while(WindowShouldClose() == false)
    {
        float movementSpeed = 100.0f * GetFrameTime();

        //direction is made out of the rotationAngle 90 in this case, made out of cosf and sinf
        //Represents the blue line vector

        Vector2 direction = { //-90 is the default rotation of the sprite
                cosf((rotationAngle - 90.0f) * DEG2RAD),
                sinf((rotationAngle - 90.0f) * DEG2RAD)
            };

        // Handle events, movement
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
        }

        if(IsKeyDown(KEY_DOWN))
        {
            shipPosition.x += direction.x * movementSpeed;
            shipPosition.y += direction.y * movementSpeed;
        }

        //movement
        for(Bullet& bullet: activeBullets)
        {
            //Manipulate the bullet
            Vector2 oldBulletPos = bullet.GetBulletPosition();

            Vector2 bulletDirection = {
                cosf((bullet.rotation - 90.0f) * DEG2RAD),
                sinf((bullet.rotation  - 90.0f) * DEG2RAD)
            };
            oldBulletPos.x += bulletDirection.x * bullet.speed;
            oldBulletPos.y += bulletDirection.y * bullet.speed;

            bullet.UpdateBulletPos(oldBulletPos);
        }

        //Spawn a bullet
        if(IsKeyPressed(KEY_SPACE))
        {
            if (!bulletPool.empty()) {
                Bullet bullet = bulletPool.front();
                bullet.rotation = rotationAngle;
                bullet.UpdateBulletPos({shipPosition.x, shipPosition.y});

                //
                activeBullets.push_back(bullet);
                bulletPool.pop();
            }
            PlaySound(sfxShoot);
        }

        //handle collision


        //draw
        BeginDrawing();
        ClearBackground(BLACK);

        // Draw Bullets
        for(auto& bullet: activeBullets)
        {
            DrawTextureV(bulletSprite, bullet.GetBulletPosition(), WHITE);
        }

        // Draw spaceship
        DrawTexturePro(
                spaceShipSprite,
                Rectangle{ 0, 0, (float)spaceShipSprite.width, (float)spaceShipSprite.height },
                Rectangle{ shipPosition.x, shipPosition.y, (float)spaceShipSprite.width, (float)spaceShipSprite.height },
                anchorPoint,
                rotationAngle,
                WHITE
            );

        //Debug bondaries drawing
        DrawRectangleRec(rightRectangle, WHITE);
        DrawRectangleRec(leftRectangle, WHITE);
        DrawRectangleRec(topRectangle, WHITE);
        DrawRectangleRec(bottomRectangle, WHITE);

        //Reset flow
        EndDrawing();
    }

    CloseWindow();
    return 0;
}