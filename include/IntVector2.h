#ifndef INT_VECTOR2_H
#define INT_VECTOR2_H

#include <stdlib.h>
#include <math.h>

typedef struct IntVector2 {
    int x;
    int y;
} IntVector2;

inline void AddIntVector2(IntVector2* result, IntVector2 a, IntVector2 b) {
    result -> x = a.x + b.x;
    result -> y = a.y + b.y;
}

inline void ScaleIntVector2(IntVector2* result, IntVector2 a, double factor) {
    result -> x = a.x * factor;
    result -> y = a.y * factor;
}

inline double LengthIntVector2(IntVector2 a) {
    return sqrt(a.x * a.x + a.y * a.y);
}

inline bool EqualsIntVector2(IntVector2 a, IntVector2 b) {
    return (a.x == b.x) && (a.y == b.y);
}

inline void NegateIntVector2(IntVector2* result, IntVector2 a) { ScaleIntVector2(result, a, -1); }

inline void SubtractIntVector2(IntVector2* result, IntVector2 a, IntVector2 b) {
    NegateIntVector2(&b, b);
    AddIntVector2(result, a, b);
}

#endif