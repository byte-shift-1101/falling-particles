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
#include <string.h>

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

inline bool FlipCoin(double probability) {
    double randValue = (rand() % 101) / 100.0;
    return randValue <= probability;
}

#define CLICK_COOLDOWN_DURATION 0.01f
#define FPS_DURATION 1.0f

Timer clickCooldown, fpsTimer;
double deltaTime;
char FPS[40];

inline void InitSystem() {
    srand((unsigned int) time(NULL));
    InitTimer(&clickCooldown, CLICK_COOLDOWN_DURATION);
    InitTimer(&fpsTimer, FPS_DURATION);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Falling Particle Simulation");
    // SetTargetFPS(1);
    HideCursor();

    snprintf(FPS, sizeof(FPS), "FPS: %lf", 60.0);
}

inline void SystemLoop() {
    ClearBackground(BLACK);
    deltaTime = GetFrameTime();
    mouseCoords = (IntVector2) {GetMouseX(), GetMouseY()};
    DecrementTimer(&clickCooldown, deltaTime);
    DecrementTimer(&fpsTimer, deltaTime);

    if (IsCursorOnScreen()) {
        DrawCircleLines(mouseCoords.x, mouseCoords.y, 2.5f * CELL_SIZE, WHITE);
        // DrawCircleLines(mouseCoords.x, mouseCoords.y, 5.0f, WHITE);
    }

    if (!IsTimeRemaining(&fpsTimer)) {
        snprintf(FPS, sizeof(FPS), "FPS: %lf", (double) 1 / deltaTime);
        RestartTimer(&fpsTimer);
    }
    DrawText(FPS, 10, 10, 20, WHITE);
}

inline void CloseSystem() {
    ShowCursor();
    CloseWindow();
}

#endif