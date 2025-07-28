#include "net/minecraft/util/Color.h"

Color::Color(int r, int g, int b) {
    mColor = (r & 255) << 16 | (g & 255) << 8 | (b & 255) | (255 << 24);
}

int Color::getRGB() {
    return mColor;
}
