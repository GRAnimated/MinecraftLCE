#pragma once

class Random {
public:
    Random();
    Random(long long seed);
    static double random();
    int nextInt(int);
    float nextFloat();
    double nextDouble();
    int nextInt();
    void setSeed(long long seed);
    long nextLong();
    bool nextBoolean();

    long val;
    bool field_8;
    long seed3;
};