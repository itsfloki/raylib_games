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
    InitAudioDevice();

    Music wall_collision_music = LoadMusicStream("resources/crash.ogg");
    Music paddle_collision_music = LoadMusicStream("resources/paddle_collision.ogg");
    wall_collision_music.looping = false;
    paddle_collision_music.looping = false;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        UpdateMusicStream(wall_collision_music);
        UpdateMusicStream(paddle_collision_music);

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
            StopMusicStream(paddle_collision_music);
            PlayMusicStream(paddle_collision_music);
        }

        if(ballPos.x <= 0)                       // left wall collision
        {
            reflectX = ballDirX < 0;
            StopMusicStream(wall_collision_music);
            PlayMusicStream(wall_collision_music);
        }
        else if(ballPos.x >= screenWidth) {      // right wall collision
            reflectX = ballDirX > 0;
            StopMusicStream(wall_collision_music);
            PlayMusicStream(wall_collision_music);
        }
        else if(ballPos.y <= 0)                  // top wall collision
        {
            reflectY = ballDirY < 0;
            StopMusicStream(wall_collision_music);
            PlayMusicStream(wall_collision_music);
        }
        else if(ballPos.y >= screenHeight)       // bottom wall collision
        {
            reflectY = ballDirY > 0;
            StopMusicStream(wall_collision_music);
            PlayMusicStream(wall_collision_music);
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
