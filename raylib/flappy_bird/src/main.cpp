#include "../globals.h"
#include "raylib.h"
#include "resource_dir.h"

int main()
{
    // Tell the window to use vsync and work on high DPI displays
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

    // Create the window and OpenGL context
    InitWindow(fn_get_window_width(), fn_get_window_height(), "Hello Raylib");

    // Utility function from resource_dir.h to find the resources folder and set it as the current working directory so
    // we can load from it
    SearchAndSetResourceDir("resources");

    // Load a texture from the resources directory
    Texture wabbit = LoadTexture("wabbit_alpha.png");

    // game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);

        DrawText("Hello Raylib", 200, 200, 20, WHITE);

        DrawTexture(wabbit, 400, 200, WHITE);

        EndDrawing();
    }

    // cleanup
    // unload our texture so it can be cleaned up
    UnloadTexture(wabbit);

    // destroy the window and cleanup the OpenGL context
    CloseWindow();

    return 0;
}
