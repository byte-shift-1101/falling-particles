#include "../include/particle.h"

void InitParticle(Particle* particle, IntVector2 mouseCoords) {
    *particle = (Particle) {
        .gridCoords = Pixel2Grid(mouseCoords),
        ._fallTimer = 0.0f,
        .color = ColorGenerator(),
        .exists = true
    };
}

bool IsInBounds(Particle* particle) {
    return IsInGrid(particle -> gridCoords);
}

bool IsAtBottom(Particle* particle) {
    return particle -> gridCoords.y == GRID_HEIGHT - 1;
}

void DrawParticle(Particle* particle) {
    IntVector2 pixelCoords = Grid2Pixel(particle -> gridCoords);
    DrawRectangle(
        pixelCoords.x,
        pixelCoords.y,
        CELL_SIZE,
        CELL_SIZE,
        particle -> color
    );
}

void SimulateFall(Particle* particle) {
    particle -> _fallTimer += deltaTime;
    if (!IsAtBottom(particle) && particle -> _fallTimer >= 1.0f) {
        particle -> gridCoords.y++;
        particle -> _fallTimer = 0.0f;
    }
}