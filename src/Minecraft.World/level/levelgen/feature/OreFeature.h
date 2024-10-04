#pragma once

#include "Minecraft.World/level/levelgen/feature/Feature.h"

class Block;

class OreFeature : public Feature {
public:
    OreFeature(const BlockState* state, int unk);

    virtual bool place(Level* level, Random& random, const BlockPos& pos) override;

private:
    const BlockState* mBlockState;
    int field_18;
};
