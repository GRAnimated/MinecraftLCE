#pragma once

#include "net/minecraft/world/level/levelgen/feature/Feature.h"

class HellFireFeature : public Feature {
public:
    // name guessed
    HellFireFeature() = default;

    bool place(Level* level, Random& random, const BlockPos& pos) override;
};
