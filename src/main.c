#include "engine.h"
#include "raymath.h"
#include <math.h>

int main() {
    // 1. Setup for 4K/High Refresh (if monitor supports it)
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT); 
    InitWindow(1280, 800, "TERRALUX - PHASE 6 [FROSTBITE CORE]");
    SetTargetFPS(144); // Higher FPS for that smooth HDR feel
    DisableCursor();

    Player p = { (Vector3){0, 2, 0}, 0, 0, 100, 0 };
    Vector3 intelPos = { 8, 0, 8 };
    float shakeIntensity = 0.0f;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        
        // --- TACTICAL MOVEMENT ---
        Vector2 mouseDelta = GetMouseDelta();
        p.yaw -= mouseDelta.x * 0.1f;
        p.pitch -= mouseDelta.y * 0.1f;
        if (p.pitch > 85.0f) p.pitch = 85.0f;
        if (p.pitch < -85.0f) p.pitch = -85.0f;

        Vector3 forward = { sinf(p.yaw * DEG2RAD), 0, cosf(p.yaw * DEG2RAD) };
        Vector3 right = { sinf((p.yaw + 90.0f) * DEG2RAD), 0, cosf((p.yaw + 90.0f) * DEG2RAD) };

        float speed = IsKeyDown(KEY_LEFT_SHIFT) ? 0.4f : 0.2f; // Sprinting
        if (IsKeyDown(KEY_W)) p.position = Vector3Add(p.position, Vector3Scale(forward, speed));
        if (IsKeyDown(KEY_S)) p.position = Vector3Subtract(p.position, Vector3Scale(forward, speed));
        if (IsKeyDown(KEY_A)) p.position = Vector3Subtract(p.position, Vector3Scale(right, speed));
        if (IsKeyDown(KEY_D)) p.position = Vector3Add(p.position, Vector3Scale(right, speed));

        // --- OBJECTIVE LOGIC ---
        if (Vector3Distance(p.position, intelPos) < 2.0f) {
            intelPos.x = (float)GetRandomValue(-20, 20);
            intelPos.z = (float)GetRandomValue(-20, 20);
            p.itemsCollected++;
            shakeIntensity = 0.5f; // TRIGGER CAMERA SHAKE
        }

        // --- CAMERA SHAKE MATH ---
        if (shakeIntensity > 0) {
            p.position.y = 2.0f + sinf(GetTime() * 50.0f) * shakeIntensity;
            shakeIntensity -= dt * 1.0f;
        } else {
            p.position.y = 2.0f; // Reset to head height
        }

        BeginDrawing();
            // Battlefield "Steel Blue/Grey" Palette
            ClearBackground((Color){ 20, 25, 30, 255 }); 
            
            Vector3 lookDir = { sinf(p.yaw*DEG2RAD), tanf(p.pitch*DEG2RAD), cosf(p.yaw*DEG2RAD) };
            Camera3D camera = { p.position, Vector3Add(p.position, lookDir), (Vector3){0, 1, 0}, 80, 0 };
            
            BeginMode3D(camera);
                DrawGrid(100, 2.0f); // Massive world scale
                // Draw Objective (Tactical Flare)
                DrawCylinder(intelPos, 0.1f, 0.1f, 4.0f, 8, ORANGE); 
                DrawSphere(intelPos, 0.5f, GOLD);
            EndMode3D();

            // --- CINEMATIC OVERLAY (Post-Processing) ---
            // Vignette
            DrawRectangleGradientV(0, 0, 1280, 150, Fade(BLACK, 0.8f), BLANK);
            DrawRectangleGradientV(0, 650, 1280, 150, BLANK, Fade(BLACK, 0.8f));

            // HUD
            DrawText("OBJECTIVE: RECOVER INTEL", 40, 40, 25, WHITE);
            DrawText(TextFormat("INTEL SECURED: %i", p.itemsCollected), 40, 75, 20, GRAY);
            
            // Crosshair
            DrawRectangle(640 - 10, 400 - 1, 20, 2, (Color){ 255, 255, 255, 150 });
            DrawRectangle(640 - 1, 400 - 10, 2, 20, (Color){ 255, 255, 255, 150 });
            
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
