#include "engine.h"
#include "raymath.h"

void Engine_Init(Entity *e) {
    e->transform.pos = (Vector3){ 0, 2, 0 }; // Start at eye level
    e->transform.yaw = 0;
    e->transform.pitch = 0;
}

void Engine_UpdateLook(Entity *e, Vector2 mouseDelta, float sensitivity) {
    // 1. Update Yaw (Horizontal) - We use negative delta because of screen coordinates
    e->transform.yaw -= mouseDelta.x * sensitivity;

    // 2. Update Pitch (Vertical)
    e->transform.pitch -= mouseDelta.y * sensitivity;

    // 3. The "Unreal" Constraint: Don't let them look past vertical (90 degrees)
    if (e->transform.pitch > 89.0f) e->transform.pitch = 89.0f;
    if (e->transform.pitch < -89.0f) e->transform.pitch = -89.0f;
}

void Engine_UpdatePhysics(Entity *e, Vector3 inputDir) {
    float dt = GetFrameTime();
    float speed = 10.0f;
    
    // We move based on the direction the player is facing (Yaw)
    Matrix rotation = MatrixRotateY(e->transform.yaw * DEG2RAD);
    Vector3 forward = Vector3Transform((Vector3){0, 0, 1}, rotation);
    Vector3 right = Vector3Transform((Vector3){1, 0, 0}, rotation);

    // Combine inputs with directions
    e->velocity.x = (forward.x * inputDir.z + right.x * inputDir.x) * speed;
    e->velocity.z = (forward.z * inputDir.z + right.z * inputDir.x) * speed;

    e->transform.pos = Vector3Add(e->transform.pos, Vector3Scale(e->velocity, dt));
}
