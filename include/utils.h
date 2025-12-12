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

#define SCREEN_WIDTH (GRID_WIDTH * CELL_SIZE)
#define SCREEN_HEIGHT (GRID_HEIGHT * CELL_SIZE)

Vector2 Grid2Pixel(Vector2 gridCoords) {
    int pixelX = GRID_BORDER + gridCoords.x * CELL_SIZE;
    int pixelY = GRID_BORDER + gridCoords.y * CELL_SIZE;
    return (Vector2) {pixelX, pixelY};
}

Vector2 Pixel2Grid(Vector2 pixelCoords) {
    int gridX = (pixelCoords.x - GRID_BORDER) / CELL_SIZE;
    int gridY = (pixelCoords.y - GRID_BORDER) / CELL_SIZE;
    return (Vector2) {gridX, gridY};
}

bool IsInGrid(Vector2 gridCoords) {
    bool xBounded = (0 <= gridCoords.x && gridCoords.x < GRID_WIDTH);
    bool yBounded = (0 <= gridCoords.y && gridCoords.y < GRID_HEIGHT);
    return xBounded && yBounded;
}

bool IsPixelInGrid(Vector2 pixelCoords) {
    Vector2 gridCoords = Pixel2Grid(pixelCoords);
    return IsInGrid(gridCoords);
}

#define COOLDOWN_PERIOD 0.1f
static double cooldownTimer;
static double deltaTime;

void RestartCooldown() { cooldownTimer = COOLDOWN_PERIOD; }
bool IsInCooldown() { return cooldownTimer > 0; }
void DecrementCooldown() {
    if (!IsInCooldown()) cooldownTimer -= deltaTime;
}

#endif