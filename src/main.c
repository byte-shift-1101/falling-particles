#include "../include/utils.h"
#include "../include/particle.h"

Particle* particles;
int particleCount;

void StartSimulation() {
    InitSystem();

    particles = (Particle*) calloc(MAX_PARTICLES, sizeof(Particle));
    for (int i = 0; i < MAX_PARTICLES; i++) {
        particles[i].exists = false;
    }
    particleCount = 0;

    ResetPresenceGrid();
}

void LoopSimulation() {
    SystemLoop();

    // Needs Refinement
    // 1. Contained in Grid Check (and overall check to see if init particle is allowed)
    // 2. Internal working of particleCount++ is a uneasy
    // if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !IsTimeRemaining(&clickCooldown) && particleCount < MAX_PARTICLES && IsPixelInGrid(mouseCoords) && !ParticleAt(Pixel2Grid(mouseCoords), particles, particleCount)) {
    //     InitParticle(&particles[particleCount], Pixel2Grid(mouseCoords));
    //     particleCount++;
    //     RestartTimer(&clickCooldown);
    // }

    double blobRadius = 2.5;
    double spawnProbability = 0.25;
    if (!IsTimeRemaining(&clickCooldown) && particleCount < MAX_PARTICLES && IsPixelInGrid(mouseCoords) && !ParticleAt(Pixel2Grid(mouseCoords), particles, particleCount)) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            InitParticle(&particles[particleCount], Pixel2Grid(mouseCoords));
            particleCount++;
        } else if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
            InitParticleBlob(Pixel2Grid(mouseCoords), blobRadius, spawnProbability, particles, &particleCount);
        }
        RestartTimer(&clickCooldown);
    }

    for (int i = 0; i < particleCount; i++) {
        DrawParticle(&particles[i]);
        SimulateFall(&particles[i], particles, particleCount);
    }

    ResetPresenceGrid();
    for (int i = 0; i < particleCount; i++) {
        IntVector2 coords = particles[i].gridCoords;
        particleGrid[coords.x][coords.y] += 1;
        if (particleGrid[coords.x][coords.y] > 1) {
            printf("Overlap detected at (%d, %d): %d particles\n", coords.x, coords.y, particleGrid[coords.x][coords.y]);
        }
    }
    printf("\n");
    // RegisterPresence(particles, particleCount);
}

void EndSimulation() {
    free(particles);

    CloseSystem();
}

int main() {
    StartSimulation();
    while (!WindowShouldClose()) {
        BeginDrawing();
            LoopSimulation();
        EndDrawing();
    }
    EndSimulation();

    return 0;
}