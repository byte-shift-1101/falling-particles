#ifndef PARTICLE_H
#define PARTICLE_H

#include "utils.h"
#include "colorManager.h"

#define MAX_PARTICLES (GRID_WIDTH * GRID_HEIGHT)

typedef struct Particle {
    IntVector2 gridCoords;
    Vector2 velocity, acceleration;
    Stopwatch fallingTimeWatch;
    Color color;
    bool exists, fallen;
} Particle;

void InitParticle(Particle*, IntVector2);
Particle* ParticleAt(IntVector2, Particle*, int);
bool IsAtBottom(Particle*);
void SimulateFall(Particle*, Particle*, int);
void DrawParticle(Particle*);

#endif