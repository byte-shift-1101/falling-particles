#ifndef GRID_MANAGER_H
#define GRID_MANAGER_H

#include "config.h"

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

inline IntVector2* GetAdjacentCellCoords(IntVector2 origin) {
    IntVector2* adjacentCoords = calloc(8, sizeof(IntVector2));

    AddIntVector2(&adjacentCoords[0], origin, UP_INT_VECTOR);
    AddIntVector2(&adjacentCoords[0], adjacentCoords[0], LEFT_INT_VECTOR);

    AddIntVector2(&adjacentCoords[1], origin, UP_INT_VECTOR);

    AddIntVector2(&adjacentCoords[2], origin, UP_INT_VECTOR);
    AddIntVector2(&adjacentCoords[2], adjacentCoords[2], RIGHT_INT_VECTOR);

    AddIntVector2(&adjacentCoords[3], origin, LEFT_INT_VECTOR);

    AddIntVector2(&adjacentCoords[4], origin, RIGHT_INT_VECTOR);

    AddIntVector2(&adjacentCoords[5], origin, DOWN_INT_VECTOR);
    AddIntVector2(&adjacentCoords[5], adjacentCoords[5], LEFT_INT_VECTOR);

    AddIntVector2(&adjacentCoords[6], origin, DOWN_INT_VECTOR);

    AddIntVector2(&adjacentCoords[7], origin, DOWN_INT_VECTOR);
    AddIntVector2(&adjacentCoords[7], adjacentCoords[7], RIGHT_INT_VECTOR);

    return adjacentCoords;
}

#endif