#include "raylib.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Draw Rotated Rectangle - raylib");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Define the rectangle and its properties
        Rectangle rec = { 400, 225, 200, 100 };
        Vector2 origin = { 100, 50 }; // Pivot point
        float rotation = 45.0f; // Rotation angle
        Color color = RED;

        // Draw the rotated rectangle
        DrawRectanglePro(rec, origin, rotation, color);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
