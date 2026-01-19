#ifndef ENGINE_H
#define ENGINE_H
#include "raylib.h"

// The Engine's definition of a Soldier
typedef struct {
    Vector3 position;
    Vector3 velocity;
    int helmetType;
    int camoType;
} Soldier;

void UpdateSoldierPhysics(Soldier *s);
#endif
