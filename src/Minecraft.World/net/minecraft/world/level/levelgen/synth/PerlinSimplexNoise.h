#pragma once

#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/level/levelgen/synth/Synth.h"

class SimplexNoise;
class Random;

class PerlinSimplexNoise : public Synth {
public:
    PerlinSimplexNoise(Random*, int);
    virtual ~PerlinSimplexNoise();
    double getValue(double, double) override;
    void init(Random*, int);
    arrayWithLength<double> getRegion(arrayWithLength<double>, double, double, int, int, double, double,
                                      double);
    arrayWithLength<double> getRegion(arrayWithLength<double>, double, double, int, int, double, double,
                                      double, double);

    SimplexNoise** m_noiseLevels;
    int m_maxOctaves;
};
