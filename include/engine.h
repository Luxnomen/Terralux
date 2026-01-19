#ifndef ENGINE_H
#define ENGINE_H
#include "raylib.h"

#define MAX_ENTITIES 100

typedef struct {
    Vector3 pos; 
    float yaw;
    float pitch;
} EngineTransform;

typedef struct {
    EngineTransform transform;
    Vector3 velocity;
    Color color;
    bool active; // Is this object in the game right now?
} Entity;

typedef struct {
    Entity entities[MAX_ENTITIES];
    int count;
} World;

void Engine_InitWorld(World *w);
void Engine_SpawnEntity(World *w, Vector3 position, Color color);
void Engine_UpdateWorld(World *w, Entity *player);
#endif
