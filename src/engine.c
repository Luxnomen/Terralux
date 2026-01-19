#include "engine.h"
#include "raymath.h"

void Engine_Init(Entity *e) {
    e->transform.pos = (Vector3){ 0, 10, 0 };
    e->velocity = (Vector3){ 0, 0, 0 };
    e->friction = 10.0f; // Higher = stops faster
    e->isGrounded = false;
}

void Engine_ApplyGravity(Entity *e, float gravity) {
    float dt = GetFrameTime();
    if (e->transform.pos.y > 0) {
        e->velocity.y -= gravity * dt;
    } else {
        e->transform.pos.y = 0;
        e->velocity.y = 0;
    }
}

void Engine_ResolveMovement(Entity *e, Vector3 inputDir, float accel, float friction) {
    float dt = GetFrameTime();

    // 1. Acceleration: Build up speed over time
    e->velocity.x += inputDir.x * accel * dt;
    e->velocity.z += inputDir.z * accel * dt;

    // 2. Friction: Gradually bleed off speed (The Frostbite Feel)
    e->velocity.x -= e->velocity.x * friction * dt;
    e->velocity.z -= e->velocity.z * friction * dt;

    // 3. Apply Velocity to Position
    e->transform.pos = Vector3Add(e->transform.pos, e->velocity);
}
