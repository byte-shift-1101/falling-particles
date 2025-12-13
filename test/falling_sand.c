#include "../include/utils.h"
#include "../include/particle.h"
#include "../include/colorManager.h"


const int maxParticles = SCREEN_HEIGHT * SCREEN_WIDTH;
Particle* particles;
int lastParticleIndex = -1;

bool HasFallen(Particle* particle) { return particle -> fallen; }

const float gravity = 100;
void SimulateFall(Particle* particle, float deltaTime) {
    particle -> vy += gravity * deltaTime;
    particle -> y += particle -> vy * deltaTime;
}

int particleCover[SCREEN_WIDTH];
void RollbackFall(Particle* particle) {
    particle -> fallen = true;

    particle -> vy = 0;
    particle -> y = particleCover[particle -> x];
    particleCover[particle -> x]--;
}

void InitSimulation() {
    particles = (Particle*) calloc(maxParticles, sizeof(Particle));
    lastParticleIndex = -1;

    for (int i = 0; i <= lastParticleIndex; i++) {
        particles[i].fallen = false;
    }

    for (int i = 0; i < SCREEN_WIDTH; i++) {
        particleCover[i] = SCREEN_HEIGHT - 1;
    }
}

void LoopSimulation() {
    float deltaTime = GetFrameTime();

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !IsInCooldown() && lastParticleIndex < maxParticles - 1) {
        MakeParticle();
        RestartCooldown();
    }

    for (int i = 0; i <= lastParticleIndex; i++) {
        Particle* particle = &particles[i];
        DrawPixel(particle -> x, particle -> y, particle -> color);
        if (HasFallen(particle)) continue;

        SimulateFall(particle, deltaTime);
        if (IsOutOfBounds(particle)) RollbackFall(particle);
    }

    DecrementTimer(deltaTime);
}

void EndSimulation() {
    free(particles);
}

int main(void) {
    srand(time(NULL));
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Falling Sand");

    InitSimulation();
    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BLACK);
            deltaTime = GetFrameTime();
            LoopSimulation();
        EndDrawing();
    }
    EndSimulation();

    CloseWindow();

    return 0;
}