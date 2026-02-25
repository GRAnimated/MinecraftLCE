#include "net/minecraft/util/Color.h"

Color::Color(int r, int g, int b) {
    m_color = (r & 255) << 16 | (g & 255) << 8 | (b & 255) | (255 << 24);
}

int Color::getRGB() {
    return m_color;
}
