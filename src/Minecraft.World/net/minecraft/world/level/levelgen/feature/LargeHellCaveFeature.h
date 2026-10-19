#pragma once

#include "net/minecraft/world/level/levelgen/feature/LargeFeature.h"

class LargeHellCaveFeature : public LargeFeature {
public:
    // name guessed
    LargeHellCaveFeature() = default;
    void addRoom(long long, int, int, ChunkPrimer*, double, double, double);
    void addTunnel(long long, int, int, ChunkPrimer*, double, double, double, float, float, float, int, int,
                   double);
    void addFeature(Level*, int, int, int, int, ChunkPrimer*) override;
};
