#pragma once

#include "net/minecraft/world/level/levelgen/feature/Feature.h"

class PumpkinFeature : public Feature {
public:
    PumpkinFeature() = default;

    bool place(Level* level, Random& random, const BlockPos& pos) override;
};
