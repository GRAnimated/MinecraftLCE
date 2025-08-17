#include "net/minecraft/world/level/levelgen/synth/PerlinNoise.h"

#include "net/minecraft/util/Mth.h"
#include "net/minecraft/world/level/levelgen/synth/ImprovedNoise.h"

#include "NX/Platform.h"

PerlinNoise::PerlinNoise(Random* random, int maxOctaves) {
    init(random, maxOctaves);
}

PerlinNoise::~PerlinNoise() {
    for (int i = 0; i < mMaxOctaves; i++) {
        delete mNoiseLevels[i];
    }
    delete[] mNoiseLevels;
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

arrayWithLength<double> PerlinNoise::getRegion(arrayWithLength<double> noise, int posX, int posY, int posZ,
                                               int width, int depth, int length, double scaleX, double scaleY,
                                               double scaleZ) {
    if (noise.data) {
        for (unsigned int i = 0; i < noise.length; i++) {
            noise[i] = 0;
        }
    } else {
        noise = arrayWithLength<double>(depth * width * length, true);
    }

    double currentSize = 1.0;

    for (int i = 0; i < mMaxOctaves; i++) {
        double scaledX = posX * currentSize * scaleX;
        double scaledY = posY * currentSize * scaleY;
        double scaledZ = posZ * currentSize * scaleZ;

        long long floorX = Mth::lfloor(scaledX);
        long long floorZ = Mth::lfloor(scaledZ);

        scaledX -= floorX;
        scaledZ -= floorZ;
        floorX = floorX % 0x1000000;
        floorZ = floorZ % 0x1000000;
        scaledX += floorX;
        scaledZ += floorZ;

        mNoiseLevels[i]->add(noise, scaledX, scaledY, scaledZ, width, depth, length, currentSize * scaleX,
                             currentSize * scaleY, currentSize * scaleZ, currentSize);

        currentSize *= 0.5;
    }

    return noise;
}

arrayWithLength<double> PerlinNoise::getRegion(arrayWithLength<double> array, int i3, int i4, int i5, int i6,
                                               double d7, double d8, double d9) {
    return getRegion(array, i3, 10, i4, i5, 1, i6, d7, 1.0, d8);
}
