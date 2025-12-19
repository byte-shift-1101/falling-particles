#include "../include/particle.h"

int SpawnParticle(IntVector2 gridCoords) {
    if (!IsInGrid(gridCoords) || ParticleAt(gridCoords)) return 0;

    particleGrid[gridCoords.x][gridCoords.y] = malloc(sizeof(Particle));
    *particleGrid[gridCoords.x][gridCoords.y] = (Particle) {
        .gridCoords = gridCoords,
        .velocity = ZERO_VECTOR,
        .acceleration = ZERO_VECTOR,
        .color = ColorGenerator()
    };

    InitStopwatch(&(particleGrid[gridCoords.x][gridCoords.y] -> fallingTimeWatch));
    return 1;
}

int MultiSpawnParticle(IntVector2 gridCoords) {
    int radiusInt = ceil(MULTI_SPAWN_RADIUS);
    int spawnedParticles = 0;

    for (int i = -radiusInt; i <= radiusInt; i++) {
        for (int j = -radiusInt; j <= radiusInt; j++) {
            if (!(LengthIntVector2((IntVector2) {i, j}) <= MULTI_SPAWN_RADIUS && FlipCoin(MULTI_SPAWN_PROBABILITY))) continue;

            IntVector2 particleCoords;
            AddIntVector2(&particleCoords, gridCoords, (IntVector2) {i, j});

            if (IsInGrid(particleCoords) && !ParticleAt(particleCoords)) {
                spawnedParticles += SpawnParticle(particleCoords);
            }
        }
    }

    return spawnedParticles;
}

Particle* ParticleAt(IntVector2 targetGridCoords) {
    if (!IsInGrid(targetGridCoords)) return NULL;
    return particleGrid[targetGridCoords.x][targetGridCoords.y];
}

void SwapParticles(Particle** a, Particle** b) {
    Particle* temp = *a;
    *a = *b;
    *b = temp;
}

void SimulateFall(Particle* particle) {
    IncrementStopwatch(&(particle -> fallingTimeWatch), deltaTime);
    
    IntVector2 gridCoordsBelow, gridCoordsBottomLeft, gridCoordsBottomRight;
    AddIntVector2(&gridCoordsBelow, particle -> gridCoords, DOWN_INT_VECTOR);
    AddIntVector2(&gridCoordsBottomLeft, particle -> gridCoords, BOTTOM_LEFT_INT_VECTOR);
    AddIntVector2(&gridCoordsBottomRight, particle -> gridCoords, BOTTOM_RIGHT_INT_VECTOR);
    Particle* particleBelow = ParticleAt(gridCoordsBelow);
    Particle* particleBottomLeft = ParticleAt(gridCoordsBottomLeft);
    Particle* particleBottomRight = ParticleAt(gridCoordsBottomRight);
    
    Vector2 deltaVelocity;
    ScaleVector2(&deltaVelocity, GRAVITY, deltaTime);
    AddVector2(&(particle -> velocity), particle -> velocity, deltaVelocity);

    if (particleBelow == NULL && IsInGrid(gridCoordsBelow) && IsTimeElapsed(&(particle -> fallingTimeWatch), (double)1 / particle -> velocity.y)) {
        SwapParticles(&particleGrid[particle -> gridCoords.x][particle -> gridCoords.y], &particleGrid[gridCoordsBelow.x][gridCoordsBelow.y]);
        AddIntVector2(&(particle -> gridCoords), particle -> gridCoords, DOWN_INT_VECTOR);
        ResetStopwatch(&(particle -> fallingTimeWatch));
    } else if (IsTimeElapsed(&(particle -> fallingTimeWatch), (double)1 / particle -> velocity.y)) {
        bool canFallBottomLeft = particleBottomLeft == NULL && IsInGrid(gridCoordsBottomLeft);
        bool canFallBottomRight = particleBottomRight == NULL && IsInGrid(gridCoordsBottomRight);

        if (canFallBottomLeft && canFallBottomRight) {
            if (FlipCoin(0.5)) {
                SwapParticles(&particleGrid[particle -> gridCoords.x][particle -> gridCoords.y], &particleGrid[gridCoordsBottomLeft.x][gridCoordsBottomLeft.y]);
                AddIntVector2(&(particle -> gridCoords), particle -> gridCoords, BOTTOM_LEFT_INT_VECTOR);
            } else {
                SwapParticles(&particleGrid[particle -> gridCoords.x][particle -> gridCoords.y], &particleGrid[gridCoordsBottomRight.x][gridCoordsBottomRight.y]);
                AddIntVector2(&(particle -> gridCoords), particle -> gridCoords, BOTTOM_RIGHT_INT_VECTOR);
            }
        } else if (canFallBottomLeft) {
            SwapParticles(&particleGrid[particle -> gridCoords.x][particle -> gridCoords.y], &particleGrid[gridCoordsBottomLeft.x][gridCoordsBottomLeft.y]);
            AddIntVector2(&(particle -> gridCoords), particle -> gridCoords, BOTTOM_LEFT_INT_VECTOR);
        } else if (canFallBottomRight) {
            SwapParticles(&particleGrid[particle -> gridCoords.x][particle -> gridCoords.y], &particleGrid[gridCoordsBottomRight.x][gridCoordsBottomRight.y]);
            AddIntVector2(&(particle -> gridCoords), particle -> gridCoords, BOTTOM_RIGHT_INT_VECTOR);
        }
        
        ResetStopwatch(&(particle -> fallingTimeWatch));
    }
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