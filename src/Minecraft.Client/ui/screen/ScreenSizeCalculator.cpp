#include "Minecraft.Client/ui/screen/ScreenSizeCalculator.h"

#include "Minecraft.Client/Minecraft.h"
#include "Minecraft.Client/Options.h"

#include <cmath>

ScreenSizeCalculator::ScreenSizeCalculator(Options* options, int scale) {
    init(options, Minecraft::GetInstance()->dword_20, Minecraft::GetInstance()->dword_24, scale);
}

ScreenSizeCalculator::ScreenSizeCalculator(Options* options, int width, int height, int scale) {
    init(options, width, height, scale);
}

void ScreenSizeCalculator::init(Options* options, int width, int height, int scale) {
    mWidth = width;
    mHeight = height;

    if (scale == -1) {
        scale = 1;
        mScale = 1;

        int maxScreenScale = options->mGuiScale;
        if (maxScreenScale == 0)
            maxScreenScale = 1000;

        if (maxScreenScale >= 2) {
            while (scale < maxScreenScale) {
                if (width / (scale + 1) < 320 || height / (scale + 1) < 240)
                    break;
                ++scale;
                mScale = scale;
            }
        }
    } else {
        mScale = scale;
    }

    mScaledWidth = (double)width / scale;
    mScaledHeight = (double)height / scale;

    mWidth = ceil(mScaledWidth);
    mHeight = ceil(mScaledHeight);
}

int ScreenSizeCalculator::getWidth() {
    return mWidth;
}

int ScreenSizeCalculator::getHeight() {
    return mHeight;
}
