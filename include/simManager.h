#ifndef SIM_MANAGER_H
#define SIM_MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#include "config.h"
#include "timer.h"
#include "particle.h"
#include "gridManager.h"

typedef struct GameState {
    // Time
    double deltaTime;
    Timer clickCooldown, displayTimer;
    char displayFPS[40], displayParticleCount[40];

    IntVector2 mouseGridCoords;

    Particle* particleGrid[GRID_WIDTH][GRID_HEIGHT];
    int particleCount;

    // Color Generation
    double currentHue;
} GameState;

inline void InitGameState(GameState* game) {
    game -> deltaTime = 0.0f;
    InitTimer(&game -> clickCooldown, CLICK_COOLDOWN_DURATION);
    InitTimer(&game -> displayTimer, FPS_DURATION);
    snprintf(game -> displayFPS, sizeof(game -> displayFPS), "FPS: %d", 0);
    snprintf(game -> displayParticleCount, sizeof(game -> displayParticleCount), "Particles: %d", 0);
    
    for (int x = 0; x < GRID_WIDTH; x++) {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            game -> particleGrid[x][y] = NULL;
        }
    }
    game -> particleCount = 0;

    game -> currentHue = 0.0;
}

inline void InitSystem(GameState* game) {
    srand((unsigned int) time(NULL));

    InitGameState(game);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Falling Particle Simulation");

    HideCursor();
}

inline void StartSystemLoop(GameState* game) {
    ClearBackground(BLACK);
    game -> deltaTime = GetFrameTime();
    game -> mouseGridCoords = Pixel2Grid((IntVector2) {GetMouseX(), GetMouseY()});

    if (!IsTimeRemaining(&game -> displayTimer)) {
        int fps = (int)(1 / game -> deltaTime);
        if (fps < 0) fps = 0;
        
        snprintf(game -> displayFPS, sizeof(game -> displayFPS), "FPS: %d", fps);
        snprintf(game -> displayParticleCount, sizeof(game -> displayParticleCount), "Particles: %d", game -> particleCount);
        RestartTimer(&game -> displayTimer);
    }
}

inline void EndSystemLoop(GameState* game) {
    if (IsCursorOnScreen()) {
        IntVector2 pixelCoords = Grid2Pixel(game -> mouseGridCoords);
        DrawCircleLines(pixelCoords.x, pixelCoords.y, MULTI_SPAWN_RADIUS * CELL_SIZE, WHITE);
    }
    
    DrawText(game -> displayFPS, 10, 10, 20, WHITE);
    DrawText(game -> displayParticleCount, 10, 40, 20, WHITE);

    DecrementTimer(&game -> clickCooldown, game -> deltaTime);
    DecrementTimer(&game -> displayTimer, game -> deltaTime);
}

inline void CloseSystem() {
    ShowCursor();
    CloseWindow();
}

#endif