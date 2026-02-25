#pragma once

class Options;

class ScreenSizeCalculator {
public:
    ScreenSizeCalculator(Options* options, int scale);
    ScreenSizeCalculator(Options* options, int width, int height, int scale);
    void init(Options* options, int width, int height, int scale);
    int getWidth();
    int getHeight();

    int m_width;
    int m_height;
    double m_scaledWidth;
    double m_scaledHeight;
    int m_scale;
};
