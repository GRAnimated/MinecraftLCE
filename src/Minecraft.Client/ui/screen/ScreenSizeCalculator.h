#pragma once

class Options;

class ScreenSizeCalculator {
public:
    ScreenSizeCalculator(Options* options, int scale);
    ScreenSizeCalculator(Options* options, int width, int height, int scale);
    void init(Options* options, int width, int height, int scale);
    int getWidth();
    int getHeight();

private:
    int mWidth;
    int mHeight;
    double mScaledWidth;
    double mScaledHeight;
    int mScale;
};
