#include "../include/particle.h"

void InitParticle(Particle* particle, IntVector2 mouseCoords) {
    *particle = (Particle) {
        .gridCoords = Pixel2Grid(mouseCoords),
        .velocity = ZERO_VECTOR,
        .acceleration = ZERO_VECTOR,
        .color = ColorGenerator(),
        .exists = true,
        .fallen = false
    };

    InitStopwatch(&(particle -> fallingTimeWatch));
}

Particle* ParticleAt(IntVector2 targetGridCoords, Particle* particles, int particleCount) {
    for (int i = 0; i < particleCount; i++) {
        if (EqualsIntVector2(particles[i].gridCoords, targetGridCoords)) {
            return &particles[i];
        }
    }
    return NULL;
}

bool IsAtBottom(Particle* particle) {
    return particle -> gridCoords.y == GRID_HEIGHT - 1;
}

bool HasStoppingParticleBelow(Particle* particleBelow) {
    return (particleBelow != NULL && particleBelow -> fallen);
}

bool HasFallingParticleBelow(Particle* particleBelow) {
    return (particleBelow != NULL && !particleBelow -> fallen);
}

bool HasFallingSpaceBelow(Particle* particle, Particle* particleBelow) {
    return !(IsAtBottom(particle) || HasStoppingParticleBelow(particleBelow));
}

bool CanFall(Particle* particle, Particle* particleBelow) {
    bool fallWaitElapsed = IsTimeElapsed(&(particle -> fallingTimeWatch), 1.0f / particle -> velocity.y);
    return HasFallingSpaceBelow(particle, particleBelow) && fallWaitElapsed;
}

void SimulateFall(Particle* particle, Particle* particles, int particleCount) {
    if (particle -> fallen) return;

    IncrementStopwatch(&(particle -> fallingTimeWatch), deltaTime);
    
    IntVector2 gridCoordsBelow;
    AddIntVector2(&gridCoordsBelow, particle -> gridCoords, DOWN_INT_VECTOR);
    Particle* particleBelow = ParticleAt(gridCoordsBelow, particles, particleCount);
    
    Vector2 deltaVelocity;
    ScaleVector2(&deltaVelocity, GRAVITY, deltaTime);
    AddVector2(&(particle -> velocity), particle -> velocity, deltaVelocity);

    if (CanFall(particle, particleBelow)) {
        if (HasFallingParticleBelow(particleBelow)) {
            particle -> velocity.y = particleBelow -> velocity.y;
        }
        
        particle -> gridCoords.y++;
        ResetStopwatch(&(particle -> fallingTimeWatch));
    }
    
    if (!HasFallingSpaceBelow(particle, particleBelow)) {
        IntVector2 gridCoordsLeft, gridCoordsRight;
        AddIntVector2(&gridCoordsLeft, particle -> gridCoords, BOTTOM_LEFT_INT_VECTOR);
        AddIntVector2(&gridCoordsRight, particle -> gridCoords, BOTTOM_RIGHT_INT_VECTOR);
        Particle* particleBelowLeft = ParticleAt(gridCoordsLeft, particles, particleCount);
        Particle* particleBelowRight = ParticleAt(gridCoordsRight, particles, particleCount);

        bool canFallLeft = !IsAtBottom(particle) && (particleBelowLeft == NULL || !particleBelowLeft -> fallen) && IsInGrid(gridCoordsLeft);
        bool canFallRight = !IsAtBottom(particle) && (particleBelowRight == NULL || !particleBelowRight -> fallen) && IsInGrid(gridCoordsRight);

        if (canFallLeft && canFallRight) {
            if (rand() % 2 == 0) {
                particle -> gridCoords.x--;
            } else {
                particle -> gridCoords.x++;
            }
        } else if (canFallLeft) {
            particle -> gridCoords.x--;
        } else if (canFallRight) {
            particle -> gridCoords.x++;
        } else {            
            particle -> fallen = true;
        }
        
        // particle -> velocity = ZERO_VECTOR;
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