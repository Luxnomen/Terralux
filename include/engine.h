#ifndef ENGINE_H
#define ENGINE_H
#include "raylib.h"

typedef struct {
    Vector3 position;
    Vector3 velocity;
    float yaw;
    float pitch;
} Engine_Entity;

void Engine_Init(Engine_Entity *e);
void Engine_Update(Engine_Entity *e);
#endif
