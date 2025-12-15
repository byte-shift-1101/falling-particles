#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "IntVector2.h"
#include "Vector2.h"
#include "timer.h"
#include "raylib.h"

#define GRID_WIDTH 100
#define GRID_HEIGHT 100
#define GRID_BORDER 10
#define CELL_SIZE 10

#define SCREEN_WIDTH (GRID_WIDTH * CELL_SIZE + 2 * GRID_BORDER)
#define SCREEN_HEIGHT (GRID_HEIGHT * CELL_SIZE + 2 * GRID_BORDER)

static Vector2 ZERO_VECTOR = {0.0f, 0.0f};
static Vector2 GRAVITY = {0.0f, 200.0f};

IntVector2 mouseCoords;
static IntVector2 DOWN_INT_VECTOR = {0, 1};
static IntVector2 BOTTOM_LEFT_INT_VECTOR = {-1, 1};
static IntVector2 BOTTOM_RIGHT_INT_VECTOR = {1, 1};

// Particle* particleGrid[GRID_WIDTH][GRID_HEIGHT];
// void ResetPresenceGrid() {
//     for (int x = 0; x < GRID_WIDTH; x++) {
//         for (int y = 0; y < GRID_HEIGHT; y++) {
//             particleGrid[x][y] = NULL;
//         }
//     }
// }

// void RegisterPresence(Particle* particles, int particleCount) {
//     for (int i = 0; i < particleCount; i++) {
//         particleGrid[particles[i].gridCoords.x][particles[i].gridCoords.y] = &particles[i];
//     }
// }

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

#define CLICK_COOLDOWN_DURATION 0.01f

Timer clickCooldown;
double deltaTime;

inline void InitSystem() {
    srand((unsigned int) time(NULL));
    InitTimer(&clickCooldown, CLICK_COOLDOWN_DURATION);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Falling Particle Simulation");
}

inline void SystemLoop() {
    ClearBackground(BLACK);
    deltaTime = GetFrameTime();
    mouseCoords = (IntVector2) {GetMouseX(), GetMouseY()};
    DecrementTimer(&clickCooldown, deltaTime);
}

inline void CloseSystem() {
    CloseWindow();
}

#endif