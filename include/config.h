#ifndef CONFIG_H
#define CONFIG_H

#include "raylib.h"
#include "Vector2.h"
#include "IntVector2.h"
#include <assert.h>

// Structs
typedef struct GameState GameState;

// Grid Parameters
#define GRID_WIDTH 100
#define GRID_HEIGHT 100
#define GRID_BORDER 10
#define CELL_SIZE 10

// Screen Parameters
#define SCREEN_WIDTH (GRID_WIDTH * CELL_SIZE + 2 * GRID_BORDER)
#define SCREEN_HEIGHT (GRID_HEIGHT * CELL_SIZE + 2 * GRID_BORDER)

// Physics Parameters
#define ZERO_VECTOR (Vector2){0.0f, 0.0f}
#define GRAVITY (Vector2){0.0f, 200.0f}

// Direction Vectors
#define UP_INT_VECTOR (IntVector2){0, -1}
#define DOWN_INT_VECTOR (IntVector2){0, 1}
#define LEFT_INT_VECTOR (IntVector2){-1, 0}
#define RIGHT_INT_VECTOR (IntVector2){1, 0}

// Timing Parameters
#define CLICK_COOLDOWN_DURATION 0.01f
#define FPS_DURATION 1.0f

// Particle Spawning Parameters
#define MULTI_SPAWN_RADIUS 3.0
#define MULTI_SPAWN_PROBABILITY 0.25

// Simulation Parameters
#define MAX_PARTICLES (GRID_WIDTH * GRID_HEIGHT)

// Color Generation Parameters
#define HUE_STEP 0.33
#define SATURATION 100
#define LIGHTNESS 50
#define MAX_Hue 360
#define MAX_SL 100

#endif