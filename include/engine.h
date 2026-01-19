#ifndef ENGINE_H
#define ENGINE_H
#include "raylib.h"

typedef struct {
    Vector3 pos; 
    float yaw;   // Left/Right rotation
    float pitch; // Up/Down rotation
} EngineTransform;

typedef struct {
    EngineTransform transform;
    Vector3 velocity;
    bool isGrounded;
} Entity;

void Engine_Init(Entity *e);
void Engine_UpdatePhysics(Entity *e, Vector3 inputDir);
// New: This function handles the mouse logic
void Engine_UpdateLook(Entity *e, Vector2 mouseDelta, float sensitivity);

#endif
