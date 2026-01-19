#include "engine.h"
#include <math.h>

int main() {
    InitWindow(1280, 800, "Terralux Engine - Fixed Controls");
    SetTargetFPS(60);
    DisableCursor();

    World myWorld;
    Engine_InitWorld(&myWorld);

    Engine_SpawnEntity(&myWorld, (Vector3){5, 1, 5}, RED);
    Engine_SpawnEntity(&myWorld, (Vector3){-5, 1, 10}, BLUE);
    Engine_SpawnEntity(&myWorld, (Vector3){0, 1, 15}, GREEN);

    Entity player = {0};
    player.transform.pos = (Vector3){0, 2, 0};
    player.transform.yaw = 0.0f;
    player.transform.pitch = 0.0f;

    while (!WindowShouldClose()) {
        // 1. Mouse Look (Pitch and Yaw)
        Vector2 mouseDelta = GetMousePositionDelta();
        player.transform.yaw -= mouseDelta.x * 0.1f;
        player.transform.pitch -= mouseDelta.y * 0.1f;
        
        // Clamp looking up/down so you don't flip over
        if (player.transform.pitch > 89.0f) player.transform.pitch = 89.0f;
        if (player.transform.pitch < -89.0f) player.transform.pitch = -89.0f;

        // 2. Calculate Directional Vectors
        Vector3 forward = {
            sinf(player.transform.yaw * DEG2RAD),
            0, // Keep movement on the flat ground
            cosf(player.transform.yaw * DEG2RAD)
        };

        Vector3 right = { 
            sinf((player.transform.yaw + 90.0f) * DEG2RAD), 
            0, 
            cosf((player.transform.yaw + 90.0f) * DEG2RAD) 
        };

        // 3. Fixed Movement (Not Inverted)
        float speed = 0.2f;
        if (IsKeyDown(KEY_W)) player.transform.pos = Vector3Add(player.transform.pos, Vector3Scale(forward, speed));
        if (IsKeyDown(KEY_S)) player.transform.pos = Vector3Subtract(player.transform.pos, Vector3Scale(forward, speed));
        if (IsKeyDown(KEY_D)) player.transform.pos = Vector3Add(player.transform.pos, Vector3Scale(right, speed));
        if (IsKeyDown(KEY_A)) player.transform.pos = Vector3Subtract(player.transform.pos, Vector3Scale(right, speed));

        // 4. Update Camera for Rendering
        // We use a separate 'viewTarget' so the camera can look up/down without moving up/down
        Vector3 viewTarget = {
            sinf(player.transform.yaw * DEG2RAD),
            tanf(player.transform.pitch * DEG2RAD),
            cosf(player.transform.yaw * DEG2RAD)
        };

        Camera3D camera = { 0 };
        camera.position = player.transform.pos;
        camera.target = Vector3Add(player.transform.pos, viewTarget);
        camera.up = (Vector3){0, 1, 0};
        camera.fovy = 75.0f;
        camera.projection = CAMERA_PERSPECTIVE;

        BeginDrawing();
            ClearBackground(SKYBLUE);
            BeginMode3D(camera);
                DrawGrid(50, 1.0f);
                for(int i = 0; i < myWorld.count; i++) {
                    if(myWorld.entities[i].active) {
                        DrawCube(myWorld.entities[i].transform.pos, 2, 2, 2, myWorld.entities[i].color);
