#pragma once

#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/level/levelgen/synth/Synth.h"

class ImprovedNoise;
class Random;

class PerlinNoise : public Synth {
public:
    PerlinNoise(Random*, int);
    virtual ~PerlinNoise();
    double getValue(double, double) override;
    void init(Random*, int);
    arrayWithLength<double> getRegion(arrayWithLength<double>, int, int, int, int, int, int, double, double,
                                      double);
    arrayWithLength<double> getRegion(arrayWithLength<double>, int, int, int, int, double, double, double);

    ImprovedNoise** m_noiseLevels;
    int m_maxOctaves;
};
