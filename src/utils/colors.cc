//
// Created by bparsy on 6/10/20.
//

#include "colors.hh"

Vec hsv(int hue, float sat, float val) {
    hue %= 360;
    while (hue < 0) hue += 360;

    if (sat < 0.f)
        sat = 0.f;
    if (sat > 1.f)
        sat = 1.f;

    if (val < 0.f)
        val = 0.f;
    if (val > 1.f)
        val = 1.f;

    int h = hue / 60;
    float f = float(hue) / 60 - (float) h;
    float p = val * (1.f - sat);
    float q = val * (1.f - sat * f);
    float t = val * (1.f - sat * (1 - f));

    switch (h) {
        default:
        case 0:
        case 6:
            return {val, t, p};
        case 1:
            return {q, val, p};
        case 2:
            return {p, val, t};
        case 3:
            return {p, q, val};
        case 4:
            return {t, p, val};
        case 5:
            return {val, p, q};
    }
}