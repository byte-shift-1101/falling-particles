#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

typedef struct Particle {
    int x;
    float y;
    float vy;
    Color color;
    bool fallen;
} Particle;

const int colorConstraints[2] = {70, 225};
Color ColorGenerator() {
    int colorRange = colorConstraints[1] - colorConstraints[0];
    return (Color) {
        .r = (rand() - colorConstraints[0]) % colorRange,
        .g = (rand() - colorConstraints[0]) % colorRange,
        .b = (rand() - colorConstraints[0]) % colorRange,
        .a = 255
    };
}

const int maxParticles = SCREEN_HEIGHT * SCREEN_WIDTH;
Particle* particles;
int lastParticleIndex = -1;
void MakeParticle() {
    lastParticleIndex++;

    particles[lastParticleIndex].x = GetMouseX();
    particles[lastParticleIndex].y = GetMouseY();
    particles[lastParticleIndex].color = ColorGenerator();
}

bool HasFallen(Particle* particle) { return particle -> fallen; }

const float gravity = 100;
void SimulateFall(Particle* particle, float deltaTime) {
    particle -> vy += gravity * deltaTime;
    particle -> y += particle -> vy * deltaTime;
}

bool IsOutOfBounds(Particle* particle) {
    return !(0 <= particle -> x && particle -> x < SCREEN_WIDTH && 0 <= particle -> y && particle -> y < SCREEN_HEIGHT);
}

int particleCover[SCREEN_WIDTH];
void RollbackFall(Particle* particle) {
    particle -> fallen = true;

    particle -> vy = 0;
    particle -> y = particleCover[particle -> x];
    particleCover[particle -> x]--;
}

const float cooldownPeriod = 0.01;
float cooldownTimer = 0;
bool RestartCooldown() { cooldownTimer = cooldownPeriod; }

bool IsInCooldown() { return cooldownTimer > 0; }

void DecrementTimer(float deltaTime) {
    if (IsInCooldown()) cooldownTimer -= deltaTime;
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
            LoopSimulation();
        EndDrawing();
    }
    EndSimulation();

    CloseWindow();

    return 0;
}