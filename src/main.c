#include "engine.h"
#include <math.h>

int main() {
    InitWindow(1280, 800, "Terralux Engine - World System");
    SetTargetFPS(60);
    DisableCursor();

    World myWorld;
    Engine_InitWorld(&myWorld);

    // Level Design: Spawn some objects
    Engine_SpawnEntity(&myWorld, (Vector3){5, 1, 5}, RED);
    Engine_SpawnEntity(&myWorld, (Vector3){-5, 1, 10}, BLUE);
    Engine_SpawnEntity(&myWorld, (Vector3){0, 1, 15}, GREEN);

    Entity player = {0};
    player.transform.pos = (Vector3){0, 2, 0};
    player.transform.yaw = 0.0f;
    player.transform.pitch = 0.0f;

    while (!WindowShouldClose()) {
        // 1. Update Mouse Look
        Vector2 mouseDelta = GetMousePositionDelta();
        player.transform.yaw -= mouseDelta.x * 0.1f;
        player.transform.pitch -= mouseDelta.y * 0.1f;
        
        // 2. Setup the Camera (FIXES THE ERROR)
        Vector3 forward = {
            sinf(player.transform.yaw * DEG2RAD),
            tanf(player.transform.pitch * DEG2RAD),
            cosf(player.transform.yaw * DEG2RAD)
        };
        
        Camera3D camera = { 0 };
        camera.position = player.transform.pos;
        camera.target = Vector3Add(player.transform.pos, forward);
        camera.up = (Vector3){0, 1, 0};
        camera.fovy = 70.0f;
        camera.projection = CAMERA_PERSPECTIVE;

        // 3. Simple Movement
        if (IsKeyDown(KEY_W)) player.transform.pos = Vector3Add(player.transform.pos, Vector3Scale(forward, 0.1f));

        BeginDrawing();
            ClearBackground(SKYBLUE);
            BeginMode3D(camera);
                DrawGrid(50, 1.0f);
                
                // Draw all entities in the world
                for(int i = 0; i < myWorld.count; i++) {
                    if(myWorld.entities[i].active) {
                        DrawCube(myWorld.entities[i].transform.pos, 2, 2, 2, myWorld.entities[i].color);
                        DrawCubeWires(myWorld.entities[i].transform.pos, 2, 2, 2, BLACK);
                    }
                }
            EndMode3D();
            
            DrawCircle(640, 400, 5, WHITE); // Crosshair
            DrawText("ENGINE RUNNING", 10, 10, 20, DARKGREEN);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
