#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct Particle Particle;

inline bool FlipCoin(double probability) {
    double randValue = (rand() % 101) / 100.0;
    return randValue <= probability;
}

inline void SwapParticles(Particle** a, Particle** b) {
    Particle* temp = *a;
    *a = *b;
    *b = temp;
}

#endif