#include "../include/colorManager.h"
#include "../include/simManager.h"

int* HSL2RGB(double h, double s, double l) {
    double chroma = (1 - fabs(2 * l - 1)) * s;
    double rgb_face_index = h / 60;
    double x = (1 - fabs(fmodf(rgb_face_index, 2.0) - 1)) * chroma;

    double r1 = 0, g1 = 0, b1 = 0;
    switch ((int)rgb_face_index) {
    case 0:
        r1 = chroma;
        g1 = x;
        break;
    case 1:
        r1 = x;
        g1 = chroma;
        break;
    case 2:
        g1 = chroma;
        b1 = x;
        break;
    case 3:
        g1 = x;
        b1 = chroma;
        break;
    case 4:
        r1 = x;
        b1 = chroma;
        break;
    case 5:
        r1 = chroma;
        b1 = x;
        break;
    }

    double m = l - chroma / 2;
    int* rgb = (int*) malloc(3 * sizeof(int));
    rgb[0] = (r1 + m) * 255;
    rgb[1] = (g1 + m) * 255;
    rgb[2] = (b1 + m) * 255;
    return rgb;
}

int* _Hue2RGB(double h) {
    return HSL2RGB(fmodf(h, MAX_Hue), (double)SATURATION / MAX_SL, (double)LIGHTNESS / MAX_SL);
}

Color SandColorGenerator() {
    static const Color sandShades[] = {
        {238, 235, 204, 255},  // Light sand       ~10%
        {226, 219, 175, 255},  // Warm sand         ~20%
        {218, 207, 162, 255},  // Classic sand      ~40% (prominent)
        {213, 196, 150, 255},  // Medium sand       ~20%
        {208, 186, 137, 255},  // Dark sand         ~10%
    };
    // Cumulative weights out of 100
    static const int cumWeights[] = {10, 20, 70, 90, 100};

    int r = GetRandomValue(1, 100);
    for (int i = 0; i < 5; i++) {
        if (r <= cumWeights[i]) return sandShades[i];
    }
    return sandShades[2];
}

Color ColorGenerator(GameState* game) {
    int* rgb = _Hue2RGB(game -> currentHue);
    game -> currentHue = fmod(game -> currentHue + HUE_STEP, MAX_Hue);
    return (Color) {
        .r = rgb[0],
        .g = rgb[1],
        .b = rgb[2],
        .a = 255
    };
}