#include "cmath"
#include "net/minecraft/util/Mth.h"
#include "net/minecraft/world/Random.h"

float Mth::sin(float v) {
    if ( !Mth::SIN ) Mth::init();

    return SIN[static_cast<int>(v * 10430.0F) & 0xFFFF];
}

float Mth::cos(float v) {
    if ( !Mth::SIN ) Mth::init();

    // original had 10430.3779296875 but .0 also matches
    return SIN[static_cast<int>(v * 10430.0f + 16384.0f) & 0xFFFF];
}

int Mth::floor(double value) {
    return (int)value - ((int)value > value);
}

int Mth::floor(float value) {
    return (int)value - ((int)value > value);
}

float Mth::sqrt(float v) {
    return std::sqrt(v);
}

float Mth::sqrt(double v) {
    return std::sqrt(v);
}

double Mth::clamp(double i, double j, double k) {
    return (i < j) ? j : (i > k) ? k : i; // gotta compress that math into one ternary :trol:
}

float Mth::clamp(float i, float j, float k) {
    return (i < j) ? j : (i > k) ? k : i;
}

int Mth::clamp(int i, int j, int k) {
    return (i < j) ? j : (i > k) ? k : i;
}

double Mth::pct(double i, double j, double k) {
    return (i - j) / (k - j);
}

double Mth::asbMax(double i, double j) {
    i = (i < 0.0) ? -i : i;
    j = (j < 0.0) ? -j : j;
    return (i > j) ? i : j;
}

int Mth::abs(int i) {
    // also matches if i > -1
    return (i >= 0) ? i : -i;
}

float Mth::abs(float i) {
    return (i >= 0.0) ? i : -i;
}

double Mth::abs(double i) {
    return (i >= 0.0) ? i : -i;
}

long Mth::lfloor(double value) {
    return (long)value - ((long)value > value);
}

double Mth::clampedLerp(double i, double j, double k) {
    if (k < 0.0) return i;
    if (1.0 < k) return j;

    return (j - i) * k + i;
}

double Mth::frac(double value) {
    return value - Mth::floor(value);
}

int Mth::nextInt(Random* random, int i, int j) {
    if (j > i)
        return random->nextInt(1 - i + j) + i;

    return i;
}

// float Mth::nextFloat(Random* random, float i, float j) {
//     if (j > i)
//         return random->nextFloat() * (j - i) + i;
//
//     return i;
// }
//
// double Mth::nextDouble(Random* random, double i, double j) {
//     if (j > i)
//         return random->nextDouble() * (j - i) + i;
//
//     return i;
// }
