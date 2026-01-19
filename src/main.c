#include "engine.h"
#include <math.h>
#include <stdio.h>

int main() {
    InitWindow(1280, 800, "Terralux: The Collection Game");
    SetTargetFPS(60);
    DisableCursor();

    // 1. Initialize Player
    Player p = { (Vector3){0, 2, 0}, 0, 0, 100, 0 };

    // 2. Define a "Goal" block
    Vector3 goalPos = { 5, 1, 5 };
    bool goalActive = true;

    while (!WindowShouldClose()) {
        // --- UPDATE ---
        Vector2 mouseDelta = GetMousePositionDelta();
        p.yaw -= mouseDelta.x * 0.1f;
        p.pitch -= mouseDelta.y * 0.1f;

        Vector3 forward = { sinf(p.yaw * DEG2RAD), 0, cosf(p.yaw * DEG2RAD) };
        Vector3 right = { sinf((p.yaw + 90.0f) * DEG2RAD), 0, cosf((p.yaw + 90.0f) * DEG2RAD) };

        if (IsKeyDown(KEY_W)) p.position = Vector3Add(p.position, Vector3Scale(forward, 0.15f));
        if (IsKeyDown(KEY_S)) p.position = Vector3Subtract(p.position, Vector3Scale(forward, 0.15f));
        if (IsKeyDown(KEY_A)) p.position = Vector3Subtract(p.position, Vector3Scale(right, 0.15f));
        if (IsKeyDown(KEY_D)) p.position = Vector3Add(p.position, Vector3Scale(right, 0.15f));

        // GAME LOGIC: Check if player "touches" the goal
        if (goalActive && Vector3Distance(p.position, goalPos) < 2.0f) {
            goalActive = false;
            p.itemsCollected++;
        }

        // --- DRAW ---
        BeginDrawing();
            ClearBackground(SKYBLUE);
            
            Camera3D camera = { p.position, Vector3Add(p.position, (Vector3){sinf(p.yaw*DEG2RAD), tanf(p.pitch*DEG2RAD), cosf(p.yaw*DEG2RAD)}), (Vector3){0, 1, 0}, 75, 0 };
            
            BeginMode3D(camera);
                DrawGrid(20, 1.0f);
                if (goalActive) {
                    DrawCube(goalPos, 2, 2, 2, GOLD);
                    DrawCubeWires(goalPos, 2, 2, 2, ORANGE);
                }
            EndMode3D();

            // UI: Show the player their progress
            DrawRectangle(10, 10, 250, 80, Fade(BLACK, 0.5f));
            DrawText(TextFormat("Items: %i", p.itemsCollected), 20, 20, 20, WHITE);
            if (!goalActive) DrawText("GOAL REACHED!", 20, 50, 20, GREEN);

            DrawCircle(640, 400, 4, WHITE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
