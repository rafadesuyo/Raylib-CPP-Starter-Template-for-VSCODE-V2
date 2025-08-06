#include <raylib.h>
#include "SpaceShip.h"
#include <iostream>
#include <vector>
#include "Bullet.h"
#include <cstddef>
#include <memory>
#include <map>
#include "raymath.h"
#include <queue>
#include <list>
#include "asteroid.h"

// Window
const int winSizeX = 800;
const int windSizeY = 800;

// Boundaries
const Rectangle rightRectangle = { winSizeX -50, 0, 50.0,windSizeY};
const Rectangle leftRectangle = {0, 0, 50.0,windSizeY};
const Rectangle topRectangle = {0, 0, winSizeX,50};
const Rectangle bottomRectangle = {0, windSizeY - 50, winSizeX,50};
const std::vector<Rectangle> BoundariesList =  {rightRectangle, leftRectangle, topRectangle, bottomRectangle};

// Asteroid spawn positions
const Vector2 spawn1 = {winSizeX, 0.0};
const Vector2 spawn2 = {0.0, windSizeY};
const std::vector<Vector2> asteroidSpawnPositions = {spawn1, spawn2};

std::queue<std::shared_ptr<Bullet>> PrewarmBulletPool()
{
    std::queue<std::shared_ptr<Bullet>> bulletPool;

    for (int i = 0; i < 30; ++i)
    {
        bulletPool.push(std::make_shared<Bullet>(1));
    }
    return bulletPool;
}


std::queue<std::shared_ptr<Asteroid>> PrewarmAsteroidPool()
{
    std::queue<std::shared_ptr<Asteroid>> asteroidPool;

    for (int i = 0; i < 30; ++i)
    {
        asteroidPool.push(std::make_shared<Asteroid>(1));
    }
    return asteroidPool;
}

void TryToSpawnAsteroid(std::list<std::shared_ptr<Asteroid>> activeAsteroids,  std::queue<std::shared_ptr<Asteroid>> inactiveAsteroidPool)
{
   // bool maximumAsteroidsSpawned = (inactiveAsteroidPool.size() = 0);
}


int main()
{
    //Player ship
    SpaceShip ship(10,20);
    float rotationAngle = 90.0;

    // Ship Position
    Vector2 shipPosition = ship.getPosition();
    const float damping = 0.99f;
    Vector2 velocity;
    float currentTrustForce = 0.0f;
    float maximumTrustForce = 1.0f;

    //Bullets queue
    std::queue<std::shared_ptr<Bullet>> bulletPool = PrewarmBulletPool();
    std::list<std::shared_ptr<Bullet>> activeBullets;

    //Asteroids queue
    std::queue<std::shared_ptr<Asteroid>> asteroidPool = PrewarmAsteroidPool();
    std::list<std::shared_ptr<Asteroid>> activeAsteroids;

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
            if(currentTrustForce < maximumTrustForce){
                currentTrustForce += 10.0f * GetFrameTime();
            }

            velocity += direction * currentTrustForce;
        }

        // Inertia movement even if not thrusting
        shipPosition += velocity * GetFrameTime();

        //Damp velocities
        velocity *= damping;
        currentTrustForce *= damping;

        // movement of bullets
        for(auto& bullet: activeBullets)
        {
            //Manipulate the bullet
            Vector2 oldBulletPos = bullet->GetBulletPosition();

            Vector2 bulletDirection = {
                cosf((bullet->rotation - 90.0f) * DEG2RAD),
                sinf((bullet->rotation  - 90.0f) * DEG2RAD)
            };
            oldBulletPos.x += bulletDirection.x * bullet->speed;
            oldBulletPos.y += bulletDirection.y * bullet->speed;

            bullet->UpdateBulletPos(oldBulletPos);
            bullet->UpdateCollisionRectanglePos(bullet->GetBulletPosition());
        }

        //Spawn a bullet
        if(IsKeyPressed(KEY_SPACE))
        {
            if (!bulletPool.empty()) {

                //Update bullet pool pos
                auto bullet = bulletPool.front();

                bullet->rotation = rotationAngle;
                bullet->UpdateBulletPos({shipPosition.x, shipPosition.y}); // so weird just use a vector2

                //Update bullet collision 
                bullet->UpdateCollisionRectanglePos(bullet->GetBulletPosition());

                //
                activeBullets.push_back(bullet);
                bulletPool.pop();
            }
            PlaySound(sfxShoot);
        }

        //handle collision
        for(auto bullet = activeBullets.begin(); bullet != activeBullets.end();)
        {
            bool collided = false;
            for (const Rectangle& boundary : BoundariesList)
            {
                if (CheckCollisionRecs((*bullet)->GetBulletCollisionRectangle(), boundary))
                {
                    bulletPool.push(*bullet);
                    bullet = activeBullets.erase(bullet);
                    collided = true;
                    break;
                }
            }
            if (!collided) ++bullet;
        }

        //draw
        BeginDrawing();
        ClearBackground(BLACK);

        // Draw Bullets
        for(auto& bullet: activeBullets)
        {
            DrawTextureV(bulletSprite, bullet->GetBulletPosition(), WHITE);
           
            // debug DrawRectangleRec(bullet->GetBulletCollisionRectangle(), WHITE);
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
        //DrawRectangleRec(rightRectangle, WHITE);
        //DrawRectangleRec(leftRectangle, WHITE);
        //DrawRectangleRec(topRectangle, WHITE);
        //DrawRectangleRec(bottomRectangle, WHITE);

        char buffer1[64];
        char buffer2[32];
        sprintf(buffer1, "Movement Speed: X: %.2f Y: %.2f", velocity.x, velocity.y);
        sprintf(buffer2, "Thrust: %.2f", currentTrustForce);


        DrawText(buffer1, 0, 0, 10, WHITE);
        DrawText(buffer2, 0, 10, 10, WHITE);

        //Reset flow
        EndDrawing();
    }

    CloseWindow();
    return 0;
}