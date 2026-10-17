#include "net/minecraft/util/Mth.h"

#include "cmath"
#include "net/minecraft/world/Random.h"

float* Mth::SIN = nullptr;
float* Mth::ATAN = nullptr;

int Mth::cached_atan_index(int x, int y) {
    return static_cast<int>(static_cast<unsigned int>(x) + static_cast<unsigned int>(y) * 40);
}

void Mth::init() {
    SIN = new float[65536];
    for (long i = 0; i < 65536; ++i)
        SIN[i] = ::sinf(static_cast<float>(static_cast<int>(i)) / 10430.3779296875f);

    ATAN = new float[cached_atan_index(40, 40) + 1];
    for (int x = 0; x < 40; ++x) {
        for (int y = 0; y < 40; ++y) {
            int index = cached_atan_index(x, y);
            ATAN[index] = ::atanf(static_cast<float>(x) / static_cast<float>(y));
        }
    }
}

float Mth::sin(float v) {
    if (!SIN)
        init();

    return SIN[static_cast<int>(v * 10430.3779296875f) & 0xFFFF];
}

float Mth::cos(float v) {
    if (!SIN)
        init();

    return SIN[static_cast<int>(v * 10430.3779296875f + 16384.0f) & 0xFFFF];
}

float Mth::sqrt(float v) {
    return std::sqrt(v);
}

float Mth::sqrt(double v) {
    return std::sqrt(v);
}

double Mth::clamp(double i, double j, double k) {
    return (i < j) ? j : (i > k) ? k : i;  // gotta compress that math into one ternary :trol:
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

MthLong Mth::lfloor(double value) {
    return static_cast<MthLong>(value) - (static_cast<MthLong>(value) > value);
}

double Mth::clampedLerp(double i, double j, double k) {
    if (k < 0.0)
        return i;
    if (1.0 < k)
        return j;

    return (j - i) * k + i;
}

double Mth::frac(double value) {
    return value - Mth::floor(value);
}

float Mth::wrapDegrees(float value) {
    value = ::fmodf(value, 360.0f);
    if (value >= 180.0f)
        value -= 360.0f;
    if (value < -180.0f)
        value += 360.0f;
    return value;
}

double Mth::wrapDegrees(double value) {
    value = ::fmod(value, 360.0);
    if (value >= 180.0)
        value -= 360.0;
    if (value < -180.0)
        value += 360.0;
    return value;
}

int64_t Mth::getSeed(int x, int y, int z) {
    // The first product wraps at 32 bits before sign extension; the final
    // products wrap at 64 bits, as in the original ARM64 integer operations.
    uint32_t wrappedX = static_cast<uint32_t>(x) * 3129871U;
    int64_t mixed = static_cast<int64_t>(static_cast<int32_t>(wrappedX))
                    ^ (static_cast<int64_t>(z) * 116129781LL) ^ static_cast<int64_t>(y);
    uint64_t seed = static_cast<uint64_t>(mixed);
    return static_cast<int64_t>((seed * 42317861ULL + 11ULL) * seed);
}

int Mth::hsvToRgb(float hue, float saturation, float value) {
    int sector = static_cast<int>(hue * 6.0f) % 6;
    float fraction = hue * 6.0f - static_cast<float>(sector);
    float low = (1.0f - saturation) * value;
    float falling = (1.0f - fraction * saturation) * value;
    float rising = (1.0f - (1.0f - fraction) * saturation) * value;
    float red, green, blue;
    switch (sector) {
    default:
        red = green = blue = 0.0f;
        break;
    case 0:
        red = value;
        green = rising;
        blue = low;
        break;
    case 1:
        red = falling;
        green = value;
        blue = low;
        break;
    case 2:
        red = low;
        green = value;
        blue = rising;
        break;
    case 3:
        red = low;
        green = falling;
        blue = value;
        break;
    case 4:
        red = rising;
        green = low;
        blue = value;
        break;
    case 5:
        red = value;
        green = low;
        blue = falling;
        break;
    }
    int r = clamp(static_cast<int>(red * 255.0f), 0, 255);
    int g = clamp(static_cast<int>(green * 255.0f), 0, 255);
    int b = clamp(static_cast<int>(blue * 255.0f), 0, 255);
    return r << 16 | g << 8 | b;
}

int Mth::nextInt(Random* random, int i, int j) {
    if (j > i)
        return random->nextInt(1 - i + j) + i;

    return i;
}

float Mth::nextFloat(Random* random, float lower, float upper) {
    if (lower >= upper)
        return lower;
    return random->nextFloat() * (upper - lower) + lower;
}

double Mth::nextDouble(Random* random, double lower, double upper) {
    if (lower >= upper)
        return lower;
    return random->nextDouble() * (upper - lower) + lower;
}

std::wstring Mth::createInsecureUUID(Random* random) {
    wchar_t text[33];
    text[32] = L'\0';
    MthLong high = (random->nextLong() & INT64_C(0xffffffffffff0fff)) | INT64_C(0x4000);
    MthLong low = (random->nextLong() & INT64_C(0x3fffffffffffffff)) | INT64_MIN;
    for (int i = 15; i != -1; --i) {
        unsigned int a = high & 15;
        unsigned int b = low & 15;
        a += a > 9 ? L'a' - 10 : L'0';
        b += b > 9 ? L'a' - 10 : L'0';
        text[i] = a;
        text[i + 16] = b;
        high >>= 4;
        low >>= 4;
    }
    return std::wstring(text);
}
