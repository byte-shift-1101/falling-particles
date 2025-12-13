#ifndef PARTICLE_H
#define PARTICLE_H

#include "utils.h"
#include "colorManager.h"

#define MAX_PARTICLES (GRID_WIDTH * GRID_HEIGHT)

typedef struct Particle {
    IntVector2 gridCoords;
    float _fallTimer;
    Color color;
    bool exists;
} Particle;

void InitParticle(Particle*, IntVector2);
bool IsInBounds(Particle*);
void DrawParticle(Particle*);
void SimulateFall(Particle*);

#endif