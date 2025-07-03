#pragma once

#include "net/minecraft/world/level/levelgen/feature/Feature.h"

class WaterlilyFeature : public Feature {
public:
    WaterlilyFeature();

    bool place(Level* level, Random& random, const BlockPos& pos) override;
};
