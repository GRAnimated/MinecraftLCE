#include "Minecraft.World/level/levelgen/synth/PerlinNoise.h"

#include "Minecraft.Util/Mth.h"
#include "Minecraft.World/level/levelgen/synth/ImprovedNoise.h"

#include "windows.h"

PerlinNoise::PerlinNoise(Random* random, int maxOctaves) {
    init(random, maxOctaves);
}

// NON_MATCHING
PerlinNoise::~PerlinNoise() {
    if (mMaxOctaves > 0) {
        for (int i = 0; i < mMaxOctaves; i++) {
            delete mNoiseLevels[i];
        }
    }
    if (mNoiseLevels) {
        delete[] mNoiseLevels;
    }
}

double PerlinNoise::getValue(double d1, double d2) {
    if (mMaxOctaves < 1)
        return 0.0;

    double value = 0.0;
    double currentSize = 1.0;

    for (int i = 0; i < mMaxOctaves; i++) {
        ImprovedNoise* noise = mNoiseLevels[i];
        value += noise->getValue(d1 * currentSize, d2 * currentSize) / currentSize;
        currentSize *= 0.5;
    }

    return value;
}

void PerlinNoise::init(Random* random, int maxOctaves) {
    MemSect(2);

    mMaxOctaves = maxOctaves;
    mNoiseLevels = new ImprovedNoise*[maxOctaves];

    if (maxOctaves >= 1) {
        for (int i = 0; i < maxOctaves; i++) {
            mNoiseLevels[i] = new ImprovedNoise(random);
        }
    }

    MemSect(0);
}

// NON_MATCHING: the octaves for loop is mismatching
arrayWithLength<double> PerlinNoise::getRegion(arrayWithLength<double> array, int i3, int i4, int i5, int i6, int i7, int i8, double d9, double d10, double d11) {
    if (array.data) {
        if (array.length) {
            for (unsigned int v20 = 0; v20 < array.length; v20++) {
                array.get(v20) = 0;
            }
        }
    } else {
        array = arrayWithLength<double>(i7 * i6 * i8, true);
    }

    if (mMaxOctaves < 1)
        return array;

    double currentSize = 1.0;

    for (int i = 0; i < mMaxOctaves; i++) {
        double test = i5 * currentSize * d10;  // maybe this should be d11?
        double test2 = i3 * currentSize * d9;

        long long v24 = Mth::lfloor(test2);
        long long v26 = Mth::lfloor(test);

        double a1 = (i3 * currentSize * d9) - v24 % 0x1000000;
        double a2 = i4 * currentSize * d10;
        double a3 = (i5 * currentSize * d11) - v26 % 0x1000000;

        mNoiseLevels[i]->add(array, a1, a2, a3, i6, i7, i8, currentSize * d9, currentSize * d10, currentSize * d11, currentSize);

        currentSize *= 0.5;
    }

    return array;
}

arrayWithLength<double> PerlinNoise::getRegion(arrayWithLength<double> array, int i3, int i4, int i5, int i6, double d7, double d8, double d9) {
    return getRegion(array, i3, 10, i4, i5, 1, i6, d7, 1.0, d8);
}
