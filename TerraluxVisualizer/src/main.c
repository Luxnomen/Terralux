#include "raylib.h"
#include <math.h>

#define BAR_COUNT 60

int main() {
    InitWindow(1280, 800, "TERRALUX VISUALIZER - XENOVI PROD");
    InitAudioDevice();
    SetTargetFPS(60);

    // Using the wav file you copied earlier
    Music music = LoadMusicStream("music.wav");
    PlayMusicStream(music);

    Camera3D camera = { (Vector3){ 25, 18, 25 }, (Vector3){ 0, 0, 0 }, (Vector3){ 0, 1, 0 }, 60, 0 };
    float barHeights[BAR_COUNT] = { 0 };

    while (!WindowShouldClose()) {
        UpdateMusicStream(music);
        float dt = GetFrameTime();
        float time = GetTime();

        for (int i = 0; i < BAR_COUNT; i++) {
            float target = (sinf(time * 4.0f + i * 0.3f) + 1.1f) * 5.0f;
            barHeights[i] = Lerp(barHeights[i], target, 10.0f * dt);
        }

        camera.position.x = sinf(time * 0.3f) * 30.0f;
        camera.position.z = cosf(time * 0.3f) * 30.0f;

        BeginDrawing();
            ClearBackground((Color){ 5, 5, 12, 255 }); 
            BeginMode3D(camera);
                DrawGrid(50, 2.0f);
                for (int i = 0; i < BAR_COUNT; i++) {
                    float angle = (float)i / BAR_COUNT * 360.0f;
                    Vector3 pos = { 15.0f * sinf(angle * DEG2RAD), 0, 15.0f * cosf(angle * DEG2RAD) };
                    DrawCube(pos, 0.4f, barHeights[i], 0.4f, (Color){ 0, 150, 255, 255 });
                    DrawCubeWires(pos, 0.4f, barHeights[i], 0.4f, SKYBLUE);
                }
            EndMode3D();
            DrawText("VISUALIZER ACTIVE: KarmaTwinBatman", 40, 40, 20, RAYWHITE);
        EndDrawing();
    }
    UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}