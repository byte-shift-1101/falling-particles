#include "../include/particle.h"

void AddParticle(Particle* particle, Vector2 mouseCoords) {
    *particle = (Particle) {
        .gridCoords = Pixel2Grid(mouseCoords),
        .color = ColorGenerator(),
        .exists = true
    };
}

bool IsInBounds(Particle* particle) {
    return IsInGrid(particle -> gridCoords);
}

void DrawParticle(Particle* particle) {
    Vector2 pixelCoords = Grid2Pixel(particle -> gridCoords);
    DrawRectangle(
        pixelCoords.x,
        pixelCoords.y,
        CELL_SIZE,
        CELL_SIZE,
        particle -> color
    );
}