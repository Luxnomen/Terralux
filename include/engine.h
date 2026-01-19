#ifndef ENGINE_H
#define ENGINE_H
#include "raylib.h"

// Renamed to EngineTransform to avoid Raylib conflicts
typedef struct {
    Vector3 pos;      // Shortened to pos for faster coding
    Vector3 rot;
    Vector3 scale;
} EngineTransform;

typedef struct {
    EngineTransform transform;
    Vector3 velocity;
    float mass;
    bool isGrounded;
} Entity;

void Engine_Init(Entity *e);
void Engine_ApplyGravity(Entity *e, float gravity);
void Engine_ResolveMovement(Entity *e, Vector3 inputDir, float speed);

#endif
