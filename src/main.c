#include "engine.h"

int main() {
    InitWindow(1280, 800, "Terralux Engine - Frostbite Physics");
    SetTargetFPS(60);

    Entity soldier = {0};
    Engine_Init(&soldier);

    while (!WindowShouldClose()) {
        Engine_ApplyGravity(&soldier, 20.0f);
        
        Vector3 move = {0};
        if (IsKeyDown(KEY_W)) move.z = 1.0f; // Normalized input
        if (IsKeyDown(KEY_S)) move.z = -1.0f;
        if (IsKeyDown(KEY_A)) move.x = 1.0f;
        if (IsKeyDown(KEY_D)) move.x = -1.0f;

        // Pass Accel (40) and Friction (10)
        Engine_ResolveMovement(&soldier, move, 40.0f, 10.0f);

        BeginDrawing();
            ClearBackground(BLACK);
            Camera3D camera = { (Vector3){10,10,10}, soldier.transform.pos, (Vector3){0,1,0}, 45, 0 };
            BeginMode3D(camera);
                DrawGrid(20, 1.0f);
                DrawCube(soldier.transform.pos, 1.0f, 2.0f, 1.0f, BLUE);
                DrawCubeWires(soldier.transform.pos, 1.0f, 2.0f, 1.0f, WHITE);
            EndMode3D();
            DrawText("PHYSICS: HEAVY (Friction Active)", 10, 10, 20, LIME);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
