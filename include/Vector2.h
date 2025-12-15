#ifndef VECTOR2_H
#define VECTOR2_H

#include <stdlib.h>
#include <math.h>
#include "raylib.h"

inline void AddVector2(Vector2* result, Vector2 a, Vector2 b) {
    result -> x = a.x + b.x;
    result -> y = a.y + b.y;
}

inline void ScaleVector2(Vector2* result, Vector2 a, double factor) {
    result -> x = a.x * factor;
    result -> y = a.y * factor;
}

inline double LengthVector2(Vector2 a) {
    return sqrt(a.x * a.x + a.y * a.y);
}

inline bool EqualsVector2(Vector2 a, Vector2 b) {
    return (a.x == b.x) && (a.y == b.y);
}

inline void NegateVector2(Vector2* result, Vector2 a) { ScaleVector2(result, a, -1); }

inline void SubtractVector2(Vector2* result, Vector2 a, Vector2 b) {
    NegateVector2(&b, b);
    AddVector2(result, a, b);
}

#endif