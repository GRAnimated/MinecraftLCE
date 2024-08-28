#pragma once

class Random {
public:
    Random();
    static double random();
    int nextInt(int);
    float nextFloat();
    double nextDouble();
    int nextInt();
    void setSeed(long long seed);
    long nextLong();

    long val;
    bool field_8;
    long seed3;
};