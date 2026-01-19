#include "engine.h"
#include "raymath.h"  // THIS WAS MISSING - It handles the Vector math
#include <math.h>

int main() {
    InitWindow(1280, 800, "Terralux: The Collection Game");
    SetTargetFPS(60);
    DisableCursor();

    Player p = { (Vector3){0, 2, 0}, 0, 0, 100, 0 };
    Vector3 goalPos = { 5, 1, 5 };
    bool goalActive = true;

    while (!WindowShouldClose()) {
        // --- UPDATE ---
        Vector2 mouseDelta = GetMouseDelta(); // Corrected function name
        p.yaw -= mouseDelta.x * 0.1f;
        p.pitch -= mouseDelta.y * 0.1f;

        // Math for forward/right movement
        Vector3 forward = { sinf(p.yaw * DEG2RAD), 0, cosf(p.yaw * DEG2RAD) };
        Vector3 right = { sinf((p.yaw + 90.0f) * DEG2RAD), 0, cosf((p.yaw + 90.0f) * DEG2RAD) };

        if (IsKeyDown(KEY_W)) p.position = Vector3Add(p.position, Vector3Scale(forward, 0.15f));
        if (IsKeyDown(KEY_S)) p.position = Vector3Subtract(p.position, Vector3Scale(forward, 0.15f));
        if (IsKeyDown(KEY_A)) p.position = Vector3Subtract(p.position, Vector3Scale(right, 0.15f));
        if (IsKeyDown(KEY_D)) p.position = Vector3Add(p.position, Vector3Scale(right, 0.15f));

        // Game Logic: Collect item
        if (goalActive && Vector3Distance(p.position, goalPos) < 2.0f) {
            goalActive = false;
            p.itemsCollected++;
        }

        // --- DRAW ---
        BeginDrawing();
            ClearBackground(SKYBLUE);
            
            // Camera setup
            Vector3 lookTarget = Vector3Add(p.position, (Vector3){
                sinf(p.yaw * DEG2RAD), 
                tanf(p.pitch * DEG2RAD), 
                cosf(p.yaw * DEG2RAD)
            });
            
            Camera3D camera = { p.position, lookTarget, (Vector3){0, 1, 0}, 75, CAMERA_PERSPECTIVE };
            
            BeginMode3D(camera);
                DrawGrid(20, 1.0f);
                if (goalActive) {
                    DrawCube(goalPos, 2, 2, 2, GOLD);
                    DrawCubeWires(goalPos, 2, 2, 2, ORANGE);
                }
            EndMode3D();

            // UI
            DrawRectangle(10, 10, 250, 80, Fade(BLACK, 0.5f));
            DrawText(TextFormat("Items: %i", p.itemsCollected), 20, 20, 20, WHITE);
            if (!goalActive) DrawText("GOAL REACHED!", 20, 50, 20, GREEN);

            DrawCircle(640, 400, 4, WHITE); // Crosshair
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
