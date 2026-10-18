#pragma once

using RandomLong = long;

class Random {
public:
    Random();
    explicit Random(long long seed);
    static double random();
    int nextInt(int bound);
    float nextFloat();
    double nextDouble();
    int nextInt();
    void setSeed(long long seed);
    RandomLong nextLong();
    bool nextBoolean();
    int next(int bits);
    double nextGaussian();

    RandomLong m_val;
    bool m_field8;
    double m_seed3;
};
