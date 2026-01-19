#include "../include/engine.h"
#include "raymath.h"

void Engine_Update(Engine_Entity *e) {
    float dt = GetFrameTime();
    float friction = 10.0f;

    // Apply weight and sliding
    e->velocity.x -= e->velocity.x * friction * dt;
    e->velocity.z -= e->velocity.z * friction * dt;

    e->position.x += e->velocity.x;
    e->position.z += e->velocity.z;
