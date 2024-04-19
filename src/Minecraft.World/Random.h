#pragma once

class Random {
public:
    Random();
    void random();
    int nextInt(int);
    float nextFloat();
    double nextDouble();
    int nextInt();
    void setSeed(long long);
    long nextLong();

    long val;
    long seed2;
    long seed3;
};