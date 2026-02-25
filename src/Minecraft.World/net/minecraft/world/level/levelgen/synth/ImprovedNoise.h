#pragma once

#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/level/levelgen/synth/Synth.h"

class Random;

class ImprovedNoise : public Synth {
public:
    ImprovedNoise(Random*);
    virtual ~ImprovedNoise();
    double getValue(double, double) override;
    void init(Random*);
    void add(arrayWithLength<double>, double, double, double, int, int, int, double, double, double, double);

    arrayWithLength<double> m_byteArray;
    double m_x;
    double m_y;
    double m_z;
};
