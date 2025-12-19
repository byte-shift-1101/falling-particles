#ifndef PARTICLE_H
#define PARTICLE_H

#include "utils.h"
#include "colorManager.h"

#define MAX_PARTICLES (GRID_WIDTH * GRID_HEIGHT)

#define MULTI_SPAWN_RADIUS 25.0
#define MULTI_SPAWN_PROBABILITY 0.25

typedef struct Particle {
    IntVector2 gridCoords;
    Vector2 velocity, acceleration;
    Stopwatch fallingTimeWatch;
    Color color;
} Particle;

int SpawnParticle(IntVector2);
int MultiSpawnParticle(IntVector2);
Particle* ParticleAt(IntVector2);
void SimulateFall(Particle*);
void DrawParticle(Particle*);

Particle* particleGrid[GRID_WIDTH][GRID_HEIGHT];
inline void ResetPresenceGrid() {
    for (int x = 0; x < GRID_WIDTH; x++) {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            particleGrid[x][y] = NULL;
        }
    }
}

inline void RegisterPresence(Particle* particles, int particleCount) {
    for (int i = 0; i < particleCount; i++) {
        particleGrid[particles[i].gridCoords.x][particles[i].gridCoords.y] = &particles[i];
    }
}

#endif