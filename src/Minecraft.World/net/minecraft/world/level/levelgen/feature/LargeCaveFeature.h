#pragma once

#include "net/minecraft/world/level/levelgen/feature/LargeFeature.h"

class LargeCaveFeature : public LargeFeature {
public:
    LargeCaveFeature() = default;
    void addFeature(Level*, int, int, int, int, ChunkPrimer*) override;
    void addRoom(long long, int, int, ChunkPrimer*, double, double, double);
    void addTunnel(long long, int, int, ChunkPrimer*, double, double, double, float, float, float, int, int,
                   double);
    bool canReplaceBlock(int, int);
};
