#include "engine.h"

int main() {
    // 1. Initialize Engine Window
    InitWindow(1280, 800, "Terralux Engine - Foundation");
    SetTargetFPS(60);

    // 2. Initialize our Entity (The Unreal "Actor")
    Entity soldier = {0};
    soldier.transform.position = (Vector3){ 0, 10.0f, 0 }; // Start high up
    soldier.mass = 1.0f;

    DisableCursor(); // Capture mouse like an FPS

    // 3. The Engine "Tick" Loop
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // Engine System: Physics Pass
        Engine_ApplyGravity(&soldier, 20.0f);
        
        // Simple Input for testing
        Vector3 movement = {0};
        if (IsKeyDown(KEY_W)) movement.z = 1.0f;
        if (IsKeyDown(KEY_S)) movement.z = -1.0f;
        Engine_ResolveMovement(&soldier, movement, 50.0f);

        // 4. Render Pass
        BeginDrawing();
            ClearBackground(DARKGRAY);
            
            // Setup Engine Camera
            Camera3D camera = { 0 };
            camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
            camera.target = soldier.transform.position;
            camera.up = (Vector3){ 0, 1.0f, 0 };
            camera.fovy = 45.0f;

            BeginMode3D(camera);
                DrawGrid(20, 1.0f); // Ground floor
                // Draw the Entity
                DrawCube(soldier.transform.position, 1.0f, 2.0f, 1.0f, BLUE);
                DrawCubeWires(soldier.transform.position, 1.0f, 2.0f, 1.0f, WHITE);
            EndMode3D();

            DrawText("ENGINE CORE: ACTIVE", 10, 10, 20, GREEN);
            DrawText("Physics: Gravity & Friction Enabled", 10, 40, 20, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
