#include "engine.h"

int main() {
    InitWindow(1280, 800, "Terralux Engine - World System");
    SetTargetFPS(60);
    DisableCursor();

    World myWorld;
    Engine_InitWorld(&myWorld);

    // This is where you "Design" your level:
    Engine_SpawnEntity(&myWorld, (Vector3){5, 1, 5}, RED);
    Engine_SpawnEntity(&myWorld, (Vector3){-5, 1, 10}, BLUE);
    Engine_SpawnEntity(&myWorld, (Vector3){0, 1, 15}, GREEN);

    Entity player = {0};
    player.transform.pos = (Vector3){0, 2, 0};

    while (!WindowShouldClose()) {
        // Update Logic (Camera/Movement code here...)
        
        BeginDrawing();
            ClearBackground(SKYBLUE);
            // Replace with your camera code...
            BeginMode3D(camera);
                DrawGrid(50, 1.0f);
                
                // THE ENGINE MAGIC: Loop through every object and draw it
                for(int i = 0; i < myWorld.count; i++) {
                    if(myWorld.entities[i].active) {
                        DrawCube(myWorld.entities[i].transform.pos, 2, 2, 2, myWorld.entities[i].color);
                    }
                }
            EndMode3D();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
