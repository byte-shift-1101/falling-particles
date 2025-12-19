#include "../include/utils.h"
#include "../include/particle.h"
#include "../include/simManager.h"

Particle* ParticleAt(IntVector2 targetGridCoords, GameState* game) {
    assert(IsInGrid(targetGridCoords));
    return game -> particleGrid[targetGridCoords.x][targetGridCoords.y];
}

bool IsAvailableAt(IntVector2 gridCoords, GameState* game) {
    return IsInGrid(gridCoords) && ParticleAt(gridCoords, game) == NULL;
}    

int SpawnParticle(IntVector2 gridCoords, GameState* game) {
    assert(IsAvailableAt(gridCoords, game));

    game -> particleGrid[gridCoords.x][gridCoords.y] = malloc(sizeof(Particle));
    *game -> particleGrid[gridCoords.x][gridCoords.y] = (Particle) {
        .gridCoords = gridCoords,
        .velocity = ZERO_VECTOR,
        .acceleration = ZERO_VECTOR,
        .color = ColorGenerator(game)
    };    

    InitStopwatch(&game -> particleGrid[gridCoords.x][gridCoords.y] -> fallingTimeWatch);
    return 1;
}    

int MultiSpawnParticle(IntVector2 gridCoords, GameState* game) {
    assert(IsAvailableAt(gridCoords, game));

    int radiusInt = ceil(MULTI_SPAWN_RADIUS);
    int spawnedParticles = 0;

    for (int i = -radiusInt; i <= radiusInt; i++) {
        for (int j = -radiusInt; j <= radiusInt; j++) {
            if (!(LengthIntVector2((IntVector2) {i, j}) <= MULTI_SPAWN_RADIUS && FlipCoin(MULTI_SPAWN_PROBABILITY))) continue;

            IntVector2 particleCoords;
            AddIntVector2(&particleCoords, gridCoords, (IntVector2) {i, j});

            if (!IsAvailableAt(particleCoords, game)) continue;
            spawnedParticles += SpawnParticle(particleCoords, game);
        }    
    }    

    return spawnedParticles;
}    

void MoveParticle(Particle* particle, IntVector2 newGridCoords, GameState* game) {
    assert(IsAvailableAt(newGridCoords, game));

    SwapParticles(&game -> particleGrid[particle -> gridCoords.x][particle -> gridCoords.y], &game -> particleGrid[newGridCoords.x][newGridCoords.y]);
    particle -> gridCoords = newGridCoords;
}

void SimulateFall(Particle* particle, GameState* game) {
    assert(particle != NULL);

    // Update Velocity
    IncrementStopwatch(&particle -> fallingTimeWatch, game -> deltaTime);
    
    Vector2 deltaVelocity;
    ScaleVector2(&deltaVelocity, GRAVITY, game -> deltaTime);
    AddVector2(&(particle -> velocity), particle -> velocity, deltaVelocity);
    
    if (!IsTimeElapsed(&particle -> fallingTimeWatch, (double)1 / particle -> velocity.y)) return;

    // Move Particle
    IntVector2* adjacentCoords = GetAdjacentCellCoords(particle -> gridCoords);
    IntVector2 gridCoordsBottomLeft = adjacentCoords[5], gridCoordsDown = adjacentCoords[6], gridCoordsBottomRight = adjacentCoords[7];

    if (IsAvailableAt(gridCoordsDown, game)) {
        MoveParticle(particle, gridCoordsDown, game);
    } else {
        bool canFallBottomLeft = IsAvailableAt(gridCoordsBottomLeft, game);
        bool canFallBottomRight = IsAvailableAt(gridCoordsBottomRight, game);

        if (canFallBottomLeft && canFallBottomRight) {
            if (FlipCoin(0.5)) {
                MoveParticle(particle, gridCoordsBottomLeft, game);
            } else {
                MoveParticle(particle, gridCoordsBottomRight, game);
            }
        } else if (canFallBottomLeft) {
            MoveParticle(particle, gridCoordsBottomLeft, game);
        } else if (canFallBottomRight) {
            MoveParticle(particle, gridCoordsBottomRight, game);
        }    
    }

    ResetStopwatch(&particle -> fallingTimeWatch);
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