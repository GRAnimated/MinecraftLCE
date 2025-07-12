#include "net/minecraft/client/renderer/texture/Texture.h"

int Texture::crispBlend(int c0, int c1) {
    int a0 = c0 >> 24 & 255;
    int a1 = c1 >> 24 & 255;
    int a = 255;
    if (a0 + a1 < 255) {
        a0 = 1;
        a1 = 1;
        a = 0;
    } else if (a0 > a1) {
        a0 = 255;
        a1 = 1;
    } else {
        a0 = 1;
        a1 = 255;
    }

    int r0 = (c0 >> 16 & 255) * a0;
    int g0 = (c0 >> 8 & 255) * a0;
    int b0 = (c0 & 255) * a0;
    int r1 = (c1 >> 16 & 255) * a1;
    int g1 = (c1 >> 8 & 255) * a1;
    int b1 = (c1 & 255) * a1;
    int r = (r0 + r1) / (a0 + a1);
    int g = (g0 + g1) / (a0 + a1);
    int b = (b0 + b1) / (a0 + a1);
    return a << 24 | r << 16 | g << 8 | b;
}
