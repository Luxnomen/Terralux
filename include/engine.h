#ifndef ENGINE_H
#define ENGINE_H
#include "raylib.h"

// The "Transform" - Every Unreal Actor has this
typedef struct {
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
} Transform;

// The "Entity" - The core of Frostbite/Unreal
typedef struct {
    Transform transform;
    Vector3 velocity;
    float mass;
    bool isGrounded;
} Entity;

// Engine Core Systems
void Engine_InitSystem();
void Engine_ApplyGravity(Entity *e, float gravity);
void Engine_ResolveMovement(Entity *e, Vector3 inputDir, float speed);
#endif
