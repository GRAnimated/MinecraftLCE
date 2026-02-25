#pragma once

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
    long nextLong();
    bool nextBoolean();
    int next(int bits);
    double nextGaussian();

    long m_val;
    bool m_field8;
    double m_seed3;
};
