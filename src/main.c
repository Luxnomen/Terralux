#include "engine.h"
#include "raymath.h"
#include <math.h>

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1280, 800, "TERRALUX - BATTLEFIELD PROTOCOL");
    SetTargetFPS(144);
    DisableCursor();

    Player p = { (Vector3){0, 2, 0}, 0, 0, 100, 0 };
    Vector3 intelPos = { 8, 0, 8 };
    float walkTimer = 0.0f;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        
        // --- INPUT & MOVEMENT ---
        Vector2 mouseDelta = GetMouseDelta();
        p.yaw -= mouseDelta.x * 0.1f;
        p.pitch -= mouseDelta.y * 0.1f;
        p.pitch = Clamp(p.pitch, -85.0f, 85.0f);

        Vector3 forward = { sinf(p.yaw * DEG2RAD), 0, cosf(p.yaw * DEG2RAD) };
        Vector3 right = { sinf((p.yaw + 90.0f) * DEG2RAD), 0, cosf((p.yaw + 90.0f) * DEG2RAD) };

        bool isMoving = false;
        float speed = IsKeyDown(KEY_LEFT_SHIFT) ? 0.4f : 0.2f;

        if (IsKeyDown(KEY_W)) { p.position = Vector3Add(p.position, Vector3Scale(forward, speed)); isMoving = true; }
        if (IsKeyDown(KEY_S)) { p.position = Vector3Subtract(p.position, Vector3Scale(forward, speed)); isMoving = true; }
        if (IsKeyDown(KEY_A)) { p.position = Vector3Subtract(p.position, Vector3Scale(right, speed)); isMoving = true; }
        if (IsKeyDown(KEY_D)) { p.position = Vector3Add(p.position, Vector3Scale(right, speed)); isMoving = true; }

        // --- WEAPON BOBBING MATH ---
        if (isMoving) walkTimer += dt * (IsKeyDown(KEY_LEFT_SHIFT) ? 14.0f : 8.0f);
        else walkTimer = Lerp(walkTimer, 0, dt * 5.0f);

        float bobOffset = sinf(walkTimer) * 0.02f;
        float swayX = -mouseDelta.x * 0.002f;
        float swayY = mouseDelta.y * 0.002f;

        BeginDrawing();
            ClearBackground((Color){ 15, 15, 18, 255 }); // Gritty dark atmosphere
            
            // 1. DRAW WORLD
            Vector3 lookDir = { sinf(p.yaw*DEG2RAD), tanf(p.pitch*DEG2RAD), cosf(p.yaw*DEG2RAD) };
            Camera3D camera = { p.position, Vector3Add(p.position, lookDir), (Vector3){0, 1, 0}, 85, 0 };
            
            BeginMode3D(camera);
                DrawGrid(100, 2.0f);
                DrawCylinder(intelPos, 0.1f, 0.1f, 5.0f, 8, ORANGE); // Objective Flare
                DrawCircle3D(intelPos, 2.0f, (Vector3){1,0,0}, 90.0f, Fade(ORANGE, 0.3f));
            EndMode3D();

            // 2. DRAW WEAPON (View Model)
            // We draw this in a second 3D pass or as a 2D overlay to prevent clipping
            BeginMode3D((Camera3D){{0,0,0}, {0,0,1}, {0,1,0}, 75, 0}); 
                // Simple Tactical Weapon Mesh (Placeholder for M4/SCAR)
                Vector3 weaponPos = { 0.5f + swayX, -0.4f + bobOffset + swayY, 0.8f };
                DrawCube(weaponPos, 0.15f, 0.2f, 0.8f, (Color){ 40, 40, 45, 255 }); // Main Body
                DrawCube(Vector3Add(weaponPos, (Vector3){0, 0.1f, -0.3f}), 0.02f, 0.08f, 0.1f, RED); // Red Dot Sight
            EndMode3D();

            // 3. HUD & POST-PROCESS
            DrawRectangleGradientV(0, 0, 1280, 200, Fade(BLACK, 0.5f), BLANK); // Top Vignette
            DrawText("BATTLEFIELD V6 - PRE-ALPHA", 40, 40, 20, (Color){255, 255, 255, 100});
            DrawCircle(640, 400, 2, GREEN); // Precise crosshair
            
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
