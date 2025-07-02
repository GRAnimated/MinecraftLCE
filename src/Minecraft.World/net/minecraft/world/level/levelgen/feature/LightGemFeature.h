#pragma once

#include "Minecraft.World/level/levelgen/feature/Feature.h"

class Block;

class LightGemFeature : public Feature {
public:
    LightGemFeature();

    virtual bool place(Level* level, Random& random, const BlockPos& pos) override;
};
