#ifndef COLOR_MANAGER_H
#define COLOR_MANAGER_H

#include "config.h"

int* HSL2RGB(double, double, double);
int* _Hue2RGB(double);
Color ColorGenerator(GameState*);

#endif