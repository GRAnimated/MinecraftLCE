#pragma once

#include "Minecraft.World/ArrayWithLength.h"
#include "Minecraft.World/level/levelgen/synth/ImprovedNoise.h"
#include "Minecraft.World/level/levelgen/synth/Synth.h"

class Random;

class PerlinNoise : public Synth {
public:
    PerlinNoise(Random*, int);
    virtual ~PerlinNoise();
    virtual double getValue(double, double) override;
    void init(Random*, int);
    arrayWithLength<double> getRegion(arrayWithLength<double>, int, int, int, int, int, int, double, double, double);
    arrayWithLength<double> getRegion(arrayWithLength<double>, int, int, int, int, double, double, double);

    ImprovedNoise** mNoiseLevels;
    int mMaxOctaves;
};
