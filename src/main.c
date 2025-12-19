#include "../include/utils.h"
#include "../include/particle.h"

int particleCount;

void StartSimulation() {
    InitSystem();

    ResetPresenceGrid();
    particleCount = 0;
}

void LoopSimulation() {
    SystemLoop();

    IntVector2 mouseGridCoords = Pixel2Grid(mouseCoords);
    if (IsInGrid(mouseGridCoords) && !ParticleAt(mouseGridCoords) && !IsTimeRemaining(&clickCooldown) && particleCount < MAX_PARTICLES) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            particleCount += SpawnParticle(mouseGridCoords);
        } else if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
            particleCount += MultiSpawnParticle(mouseGridCoords);
        }
        RestartTimer(&clickCooldown);
    }

    int checkCount = 0;
    for (int x = GRID_WIDTH - 1; x >= 0; x--) {
        for (int y = GRID_HEIGHT - 1; y >= 0; y--) {
            Particle* particle = particleGrid[x][y];
            if (particle) {
                DrawParticle(particle);
                SimulateFall(particle);
                checkCount++;
            }
        }
    }
}

void EndSimulation() {
    for (int x = 0; x < GRID_WIDTH; x++) {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            if (particleGrid[x][y]) {
                free(particleGrid[x][y]);
            }
        }
    }

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