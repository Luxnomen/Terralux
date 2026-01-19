#include "engine.h"
#include "raymath.h"

void Engine_Init(Entity *e) {
    e->transform.pos = (Vector3){ 0, 10, 0 };
    e->velocity = (Vector3){ 0, 0, 0 };
    e->isGrounded = false;
}

void Engine_ApplyGravity(Entity *e, float gravity) {
    float dt = GetFrameTime();
    if (e->transform.pos.y > 0) {
        e->velocity.y -= gravity * dt;
        e->isGrounded = false;
    } else {
        e->transform.pos.y = 0;
        e->velocity.y = 0;
        e->isGrounded = true;
    }
}

void Engine_ResolveMovement(Entity *e, Vector3 inputDir, float speed) {
    float dt = GetFrameTime();
    e->velocity.x = inputDir.x * speed * dt;
    e->velocity.z = inputDir.z * speed * dt;
    e->transform.pos = Vector3Add(e->transform.pos, e->velocity);
}
