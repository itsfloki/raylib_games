#include "raylib.h"

int main(void)
{
    const int screenWidth = 900;
    const int screenHeight = 550;

    // ball position & motion
    int posX = screenWidth / 2;
    int posY = screenHeight / 2;
    int ball_dir_x, ball_dir_y;

    ball_dir_x = ball_dir_y = 3;

    // paddle properties
    int paddleX, paddleY, paddleWidth, paddleHeight;

    paddleWidth = 150;
    paddleHeight = 10;

    paddleX = screenWidth / 2 - 50;
    paddleY = 500;
    

    InitWindow(screenWidth, screenHeight, "Breakout game");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // paddle movement
        if(IsKeyPressed(KEY_RIGHT))
        {
            paddleX += 25;
        }
        if(IsKeyPressed(KEY_LEFT))
        {
            paddleX -= 25;
        }

        bool reflect_x = false;
        bool reflect_y = false;

        if(posX <= 0)                       // left wall collision
        {
            reflect_x = ball_dir_x < 0;
        }
        else if(posX >= screenWidth) {      // right wall collision
            reflect_x = ball_dir_x > 0;
        }

        if(posY <= 0)                       // top wall collision
        {
            reflect_y = ball_dir_y < 0;
        }
        else if(posY >= screenHeight)       // bottom wall collision
        {
            reflect_y = ball_dir_y > 0;
        } 

        if(reflect_x) {
            ball_dir_x = -ball_dir_x;
        }
        if(reflect_y) {
            ball_dir_y = -ball_dir_y;
        }

        posX += ball_dir_x;
        posY += ball_dir_y;


        BeginDrawing();

            ClearBackground(BLACK);

            DrawCircle(posX, posY, 15, WHITE);
            DrawRectangle(paddleX, paddleY, paddleWidth, paddleHeight, RED);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
