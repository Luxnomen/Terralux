#include "engine.h"

int main() {
    InitWindow(1280, 800, "Terralux Engine - FPS Look");
    SetTargetFPS(60);
    DisableCursor(); // Hide the mouse and lock it to center

    Entity player;
    Engine_Init(&player);

    while (!WindowShouldClose()) {
        // 1. Capture Mouse Movement
        Vector2 mouseDelta = GetMousePositionDelta();
        Engine_UpdateLook(&player, mouseDelta, 0.1f);

        // 2. Capture Keyboard Movement
        Vector3 moveInput = {0};
        if (IsKeyDown(KEY_W)) moveInput.z = 1.0f;
        if (IsKeyDown(KEY_S)) moveInput.z = -1.0f;
        if (IsKeyDown(KEY_A)) moveInput.x = 1.0f;
        if (IsKeyDown(KEY_D)) moveInput.x = -1.0f;
        Engine_UpdatePhysics(&player, moveInput);

        // 3. Calculate the Camera view based on Engine Look math
        Camera3D camera = { 0 };
        camera.position = player.transform.pos;
        // Math to find the spot the player is looking at
        Vector3 lookTarget = Vector3Add(player.transform.pos, (Vector3){
            sinf(player.transform.yaw * DEG2RAD),
            tanf(player.transform.pitch * DEG2RAD),
            cosf(player.transform.yaw * DEG2RAD)
        });
        camera.target = lookTarget;
        camera.up = (Vector3){0, 1, 0};
        camera.fovy = 70.0f;

        BeginDrawing();
            ClearBackground(SKYBLUE);
            BeginMode3D(camera);
                DrawGrid(50, 1.0f);
                for(int i = -5; i < 5; i++) DrawCube((Vector3){i*4, 1, 10}, 2, 2, 2, RED);
            EndMode3D();
            DrawCircle(640, 400, 4, GREEN); // Crosshair
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
