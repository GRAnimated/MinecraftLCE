#pragma once

#include "net/minecraft/world/level/levelgen/feature/Feature.h"

class Block;

class LightGemFeature : public Feature {
public:
    LightGemFeature();

    bool place(Level* level, Random& random, const BlockPos& pos) override;
};
