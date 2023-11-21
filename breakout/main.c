#include <stdio.h>
#include "raylib.h"
#include "raymath.h"

int main(void)
{
    const int screenWidth = 900;
    const int screenHeight = 550;

    // ball position & motion
    Vector2 ballPos = { (float) screenWidth / 2, (float) screenHeight / 2 };
    int ballDirX, ballDirY;

    ballDirX = ballDirY = 240;

    // paddle properties
    Rectangle paddle = { (float) screenWidth / 2 - 50, 500.0, 150.0, 10.0 };
    int paddleSpeed = 300;

    InitWindow(screenWidth, screenHeight, "Breakout game");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // paddle movement
        if(IsKeyDown(KEY_RIGHT))
        {
            paddle.x += paddleSpeed * GetFrameTime();
        }
        if(IsKeyDown(KEY_LEFT))
        {
            paddle.x -= paddleSpeed * GetFrameTime();
        }

        bool reflectX = false;
        bool reflectY = false;

        // check collision of ball with paddle
        if(CheckCollisionCircleRec(ballPos, 15, paddle))
        {
            reflectX = true;
            reflectY = true;
        }

        if(ballPos.x <= 0)                       // left wall collision
        {
            reflectX = ballDirX < 0;
        }
        else if(ballPos.x >= screenWidth) {      // right wall collision
            reflectX = ballDirX > 0;
        }
        else if(ballPos.y <= 0)                  // top wall collision
        {
            reflectY = ballDirY < 0;
        }
        else if(ballPos.y >= screenHeight)       // bottom wall collision
        {
            reflectY = ballDirY > 0;
        } 
        
        // check reflection of ball
        if(reflectX)
        {
            ballDirX = -ballDirX;
        }
        if(reflectY)
        {
            ballDirY = -ballDirY;
        }

        ballPos.x += ballDirX * GetFrameTime();
        ballPos.y += ballDirY * GetFrameTime();

        BeginDrawing();

            ClearBackground(BLACK);

            DrawCircleV(ballPos, 15, RED);
            DrawRectangleRec(paddle, YELLOW);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
