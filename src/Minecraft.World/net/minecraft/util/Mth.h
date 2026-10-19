#pragma once

#include <cstdint>
#include <string>

class Random;

// Meth
class Mth {
public:
    static constexpr float PI = 3.1415927;

    static float* SIN;
    static float* ATAN;

    static float sin(float);
    static float cos(float);
    static int floor(double);
    static int floor(float);
    static int ceil(float);
    static float sqrt(float v);
    static float sqrt(double v);
    static double clamp(double, double, double);
    static float clamp(float, float, float);
    static int clamp(int, int, int);
    static double pct(double i, double j, double k);
    static double asbMax(double i, double j);  // asb
    static int abs(int i);
    static float abs(float i);
    static double abs(double i);
    static float wrapDegrees(float);
    static double wrapDegrees(double);
    static int cached_atan_index(int, int);
    static void init();
    static long lfloor(double);
    static long round(double);
    static double clampedLerp(double, double, double);
    static double frac(double);
    static int hsvToRgb(float, float, float);
    static int nextInt(Random* random, int i, int j);
    static float nextFloat(Random* random, float i, float j);
    static double nextDouble(Random* random, double i, double j);
    static std::wstring createInsecureUUID(Random* random) asm("createInsecureUUID__3MthSFP6Random");
    static int64_t getSeed(int, int, int);
};
