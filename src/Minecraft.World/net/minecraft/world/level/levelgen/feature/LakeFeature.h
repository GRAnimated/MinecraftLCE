#pragma once

#include "Minecraft.World/level/levelgen/feature/Feature.h"

class Block;

class LakeFeature : public Feature {
public:
    LakeFeature(Block* block);

    virtual bool place(Level* level, Random& random, const BlockPos& pos) override;

private:
    Block* mBlock;
};
