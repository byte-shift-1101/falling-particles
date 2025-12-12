#ifndef PARTICLE_H
#define PARTICLE_H

#include "utils.h"
#include "colorManager.h"

typedef struct Particle {
    Vector2 gridCoords;
    Color color;
    bool exists;
} Particle;

void AddParticle(Particle*);
bool IsInBounds(Particle*);

#endif