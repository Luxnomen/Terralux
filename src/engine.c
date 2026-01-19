#include "engine.h"
#include "raymath.h"

void Engine_InitWorld(World *w) {
    w->count = 0;
    for(int i = 0; i < MAX_ENTITIES; i++) w->entities[i].active = false;
}

void Engine_SpawnEntity(World *w, Vector3 position, Color color) {
    if (w->count < MAX_ENTITIES) {
        Entity *e = &w->entities[w->count];
        e->transform.pos = position;
        e->color = color;
        e->active = true;
        w->count++;
    }
}
