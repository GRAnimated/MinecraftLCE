#pragma once

#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/level/levelgen/synth/Synth.h"

class Random;

class ImprovedNoise : public Synth {
public:
    ImprovedNoise(Random*);
    virtual ~ImprovedNoise();
    double getValue(double, double) override;
    double getValue(double, double, double);
    void init(Random*);
    void add(arrayWithLength<double>, double, double, double, int, int, int, double, double, double, double);
    double grad(int, double, double, double);
    double grad(int, double, double);
    static double lerp(double, double, double);

    int* m_permutations;
    // The binary leaves these eight bytes untouched; the offsets begin at 0x18.
    char m_padding[8];
    double m_x;
    double m_y;
    double m_z;

    static double GRAD_X[16];
    static double GRAD_Y[16];
    static double GRAD_Z[16];
    static double GRAD_2D_X[16];
    static double GRAD_2D_Z[16];
};
