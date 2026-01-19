#include "engine.h"
#include "raymath.h"

void Engine_ApplyGravity(Entity *e, float gravity) {
    float dt = GetFrameTime();
    if (!e->isGrounded) {
        e->velocity.y -= gravity * dt; // Constant pull down
    }
}

void Engine_ResolveMovement(Entity *e, Vector3 inputDir, float speed) {
    float dt = GetFrameTime();
    float friction = 10.0f;

    // Apply Acceleration based on input
    e->velocity.x += inputDir.x * speed * dt;
    e->velocity.z += inputDir.z * speed * dt;

    // Apply Friction (This gives that "heavy" Frostbite feel)
    e->velocity.x -= e->velocity.x * friction * dt;
    e->velocity.z -= e->velocity.z * friction * dt;

    // Update Position
    e->transform.position = Vector3Add(e->transform.position, e->velocity);
}
