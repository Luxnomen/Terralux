#ifndef ENGINE_H
#define ENGINE_H
#include "raylib.h"

typedef struct {
    Vector3 pos; 
    Vector3 rot;
    Vector3 scale;
} EngineTransform;

typedef struct {
    EngineTransform transform;
    Vector3 velocity;
    float mass;
    float friction; // How fast we slow down
    bool isGrounded;
} Entity;

void Engine_Init(Entity *e);
void Engine_ApplyGravity(Entity *e, float gravity);
// We added friction and acceleration parameters here
void Engine_ResolveMovement(Entity *e, Vector3 inputDir, float accel, float friction);

#endif
