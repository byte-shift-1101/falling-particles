#include "../include/utils.h"
#include "../include/particle.h"
#include "../include/simManager.h"

GameState game;
void StartSimulation() {
    InitSystem(&game);
}

void LoopSimulation() {    
    assert(game.particleCount <= MAX_PARTICLES);

    StartSystemLoop(&game);
    
    if (IsAvailableAt(game.mouseGridCoords, &game) && !IsTimeRemaining(&game.clickCooldown)) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            game.particleCount += SpawnParticle(game.mouseGridCoords, &game);
        } else if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
            game.particleCount += MultiSpawnParticle(game.mouseGridCoords, &game);
        }
        RestartTimer(&game.clickCooldown);
    }

    for (int x = GRID_WIDTH - 1; x >= 0; x--) {
        for (int y = GRID_HEIGHT - 1; y >= 0; y--) {
            Particle* particle = game.particleGrid[x][y];
            if (particle) {
                DrawParticle(particle);
                SimulateFall(particle, &game);
            }
        }
    }

    EndSystemLoop(&game);
}

void EndSimulation() {
    for (int x = 0; x < GRID_WIDTH; x++) {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            if (game.particleGrid[x][y]) {
                free(game.particleGrid[x][y]);
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