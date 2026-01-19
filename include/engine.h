#ifndef ENGINE_H
#define ENGINE_H
#include "raylib.h"

typedef struct {
    Vector3 position;
    float yaw;
    float pitch;
    int health;
    int itemsCollected;
} Player;

#endif
