#pragma once

#include "net/minecraft/world/ArrayWithLength.h"

class Random;

/** The binary's octave objects have no vtable; the permutation pointer is at 0.
 */
class SimplexNoise {
public:
    explicit SimplexNoise(Random*);
    ~SimplexNoise();
    void init(Random*);
    double getValue(double, double);
    void add(arrayWithLength<double>, double, double, int, int, double, double, double);
    static int fastFloor(double);
    static double dot(const int*, double, double);

    int* m_permutations;
    char m_padding[8];
    double m_x;
    double m_y;
    double m_z;

    static const int GRAD[12][3];
    static double F2;
    static double G2;
};
