#include "net/minecraft/world/Random.h"

#include "NX/Platform.h"

#include "cmath"

// TODO: Move this
Random gRandomInstance = Random();

Random::Random() {
    long long seed;
    QueryPerformanceCounter(&seed);

    seed += 0x1ED8B55FAC9DEC;

    setSeed(seed);
}

Random::Random(long long seed) {
    this->setSeed(seed);
}

double Random::random() {
    return gRandomInstance.nextDouble();
}

int Random::nextInt(int a1) {
    int v4;  // w0
    int v5;  // w8

    // why does ida fuck up with math so much
    // ghidra gave 10x better decompilation
    // except for the return statement here
    if ((a1 & -a1) == a1)
        return (static_cast<long>(this->next(31)) * a1) >> 31;

    do {
        v5 = this->next(31);
        v4 = v5 % a1;
    } while (v5 - v4 + (a1 - 1) < 0);

    return v4;
}

float Random::nextFloat() {
    return this->next(24) * (float)0x33800000;
}

double Random::nextDouble() {
    return ((static_cast<long>(this->next(26)) << 27) + this->next(27)) * 1.11022302e-16;
}

int Random::nextInt() {
    return this->next(32);
}

void Random::setSeed(long long seed) {
    val = (seed & 0xFFFFFFFFFFFF) ^ 0x5DEECE66D;
    field_8 = false;
}

long Random::nextLong() {
    return (static_cast<long>(this->next(32)) << 32) + this->next(32);
}

bool Random::nextBoolean() {
    return this->next(1) != 0;
}

int Random::next(int bits) {
    this->val = (0x5DEECE66DLL * this->val + 11) & 0xFFFFFFFFFFFFLL;
    return this->val >> (48 - bits);
}

double Random::nextGaussian() {
    double v4;  // d9
    double v6;  // d10
    double v7;  // d8

    if (this->field_8) {
        this->field_8 = false;
        return this->seed3;
    }

    do {
        const double v3 = this->nextDouble();
        v4 = v3 + v3 - 1;  // `+ -1.0` :sob:

        const double v5 = this->nextDouble();
        v6 = v5 + v5 - 1;

        v7 = v4 * v4 + v6 * v6;
    } while (v7 >= 1.0 || v7 == 0.0);

    const double v9 = sqrt(log(v7) * -2.0 / v7);

    this->field_8 = true;
    this->seed3 = v6 * v9;

    return v4 * v9;
}
