#pragma once

#include "net/minecraft/world/level/levelgen/feature/Feature.h"

class Block;

class LightGemFeature : public Feature {
public:
    // name guessed
    LightGemFeature() = default;

    bool place(Level* level, Random& random, const BlockPos& pos) override;
};
