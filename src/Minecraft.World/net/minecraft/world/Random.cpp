#include "net/minecraft/world/Random.h"

#include "NX/Platform.h"

// TODO: Move this
Random gRandomInstance = Random();

Random::Random() {
    long long seed;
    QueryPerformanceCounter(&seed);

    seed += 0x1ED8B55FAC9DEC;

    setSeed(seed);
}

double Random::random() {
    return gRandomInstance.nextDouble();
}

void Random::setSeed(long long seed) {
    val = (seed & 0xFFFFFFFFFFFF) ^ 0x5DEECE66D;
    field_8 = false;
}