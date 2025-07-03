#pragma once

#include "net/minecraft/world/level/levelgen/feature/Feature.h"

class HellFireFeature : public Feature {
public:
    HellFireFeature();

    bool place(Level* level, Random& random, const BlockPos& pos) override;
};
