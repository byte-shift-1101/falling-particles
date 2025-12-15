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

    // ResetPresenceGrid();
}

void LoopSimulation() {
    SystemLoop();

    // Needs Refinement
    // 1. Contained in Grid Check (and overall check to see if init particle is allowed)
    // 2. Internal working of particleCount++ is a uneasy
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !IsTimeRemaining(&clickCooldown) && particleCount < MAX_PARTICLES && IsPixelInGrid(mouseCoords) && !ParticleAt(Pixel2Grid(mouseCoords), particles, particleCount)) {
        InitParticle(&particles[particleCount], mouseCoords);
        particleCount++;
        RestartTimer(&clickCooldown);
    }

    for (int i = 0; i < particleCount; i++) {
        DrawParticle(&particles[i]);
        SimulateFall(&particles[i], particles, particleCount);
    }

    // ResetPresenceGrid();
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