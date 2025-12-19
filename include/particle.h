#ifndef PARTICLE_H
#define PARTICLE_H

#include "config.h"
#include "timer.h"
#include "colorManager.h"

typedef struct Particle {
    IntVector2 gridCoords;
    Vector2 velocity, acceleration;
    Stopwatch fallingTimeWatch;
    Color color;
} Particle;

Particle* ParticleAt(IntVector2, GameState*);
bool IsAvailableAt(IntVector2, GameState*);
int SpawnParticle(IntVector2, GameState*);
int MultiSpawnParticle(IntVector2, GameState*);

void MoveParticle(Particle*, IntVector2, GameState*);
void SimulateFall(Particle*, GameState*);

void DrawParticle(Particle*);

#endif