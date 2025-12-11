#include "raylib.h"

const int screenWidth = 800;
const int screenHeight = 450;

int main(void)
{
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}