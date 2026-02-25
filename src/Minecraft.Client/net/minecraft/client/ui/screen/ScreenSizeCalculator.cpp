#include "net/minecraft/client/ui/screen/ScreenSizeCalculator.h"

#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/client/Options.h"

#include <cmath>

ScreenSizeCalculator::ScreenSizeCalculator(Options* options, int scale) {
    init(options, Minecraft::GetInstance()->m_width, Minecraft::GetInstance()->m_height, scale);
}

ScreenSizeCalculator::ScreenSizeCalculator(Options* options, int width, int height, int scale) {
    init(options, width, height, scale);
}

void ScreenSizeCalculator::init(Options* options, int width, int height, int scale) {
    m_width = width;
    m_height = height;

    if (scale == -1) {
        scale = 1;
        m_scale = 1;

        int maxScreenScale = options->m_guiScale;
        if (maxScreenScale == 0)
            maxScreenScale = 1000;

        if (maxScreenScale >= 2) {
            while (scale < maxScreenScale) {
                if (width / (scale + 1) < 320 || height / (scale + 1) < 240)
                    break;
                ++scale;
                m_scale = scale;
            }
        }
    } else {
        m_scale = scale;
    }

    m_scaledWidth = (double)width / scale;
    m_scaledHeight = (double)height / scale;

    m_width = ceil(m_scaledWidth);
    m_height = ceil(m_scaledHeight);
}

int ScreenSizeCalculator::getWidth() {
    return m_width;
}

int ScreenSizeCalculator::getHeight() {
    return m_height;
}
