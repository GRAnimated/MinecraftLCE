#pragma once

class Mth {
public:
    static float sin(float);
    static float cos(float);
    static int floor(double);
    static int floor(float);
    static double clamp(double, double, double);
    static float clamp(float, float, float);
    static int clamp(int, int, int);
    static float wrapDegrees(float);
    static void cached_atan_index(int, int);
    static void init(void);
    static long lfloor(double);
    static void clampedLerp(double, double, double);
    static void frac(double);
    static int hsvToRgb(float, float, float);
};
