#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "raylib.h"

#define GRID_WIDTH 40
#define GRID_HEIGHT 40
#define GRID_BORDER 10
#define CELL_SIZE 10

#define SCREEN_WIDTH (GRID_WIDTH * CELL_SIZE + 2 * GRID_BORDER)
#define SCREEN_HEIGHT (GRID_HEIGHT * CELL_SIZE + 2 * GRID_BORDER)

typedef struct IntVector2 {
    int x, y;
} IntVector2;

inline IntVector2 Grid2Pixel(IntVector2 gridCoords) {
    int pixelX = GRID_BORDER + gridCoords.x * CELL_SIZE;
    int pixelY = GRID_BORDER + gridCoords.y * CELL_SIZE;
    return (IntVector2) {pixelX, pixelY};
}

inline IntVector2 Pixel2Grid(IntVector2 pixelCoords) {
    int gridX = (pixelCoords.x - GRID_BORDER) / CELL_SIZE;
    int gridY = (pixelCoords.y - GRID_BORDER) / CELL_SIZE;
    return (IntVector2) {gridX, gridY};
}

inline bool IsInGrid(IntVector2 gridCoords) {
    bool xBounded = (0 <= gridCoords.x && gridCoords.x < GRID_WIDTH);
    bool yBounded = (0 <= gridCoords.y && gridCoords.y < GRID_HEIGHT);
    return xBounded && yBounded;
}

inline bool IsPixelInGrid(IntVector2 pixelCoords) {
    IntVector2 gridCoords = Pixel2Grid(pixelCoords);
    return IsInGrid(gridCoords);
}

#define COOLDOWN_PERIOD 0.1f
static double cooldownTimer;
double deltaTime;

inline void RestartCooldown() { cooldownTimer = COOLDOWN_PERIOD; }
inline bool IsInCooldown() { return cooldownTimer > 0; }
inline void DecrementCooldown() {
    if (IsInCooldown()) cooldownTimer -= deltaTime;
}

inline void InitSystem() {
    srand((unsigned int) time(NULL));
    cooldownTimer = 0;
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Falling Particle Simulation");
}

inline void SystemLoop() {
    ClearBackground(BLACK);
    deltaTime = GetFrameTime();
    DecrementCooldown();
}

inline void CloseSystem() {
    CloseWindow();
}

#endif