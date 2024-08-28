#include "Minecraft.World/Random.h"

#include "windows.h"

// TODO: Move this
static Random* gRandomInstance = new Random();

Random::Random() {
    long long seed;
    QueryPerformanceCounter(&seed);

    seed += 0x1ED8B55FAC9DEC;

    setSeed(seed);
}

double Random::random() {
    return gRandomInstance->nextDouble();
}

void Random::setSeed(long long seed) {
    val = (seed & 0xFFFFFFFFFFFF) ^ 0x5DEECE66D;
    field_8 = false;
}