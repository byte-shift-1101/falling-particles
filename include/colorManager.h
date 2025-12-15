#ifndef COLOR_MANAGER_H
#define COLOR_MANAGER_H

#include "utils.h"

#define HUE_STEP 0.33
#define SATURATION 100
#define LIGHTNESS 50
#define MAX_Hue 360
#define MAX_SL 100

static double initialHue = 0;
int* HSL2RGB(double, double, double);
int* _Hue2RGB(double);
Color ColorGenerator();

#endif