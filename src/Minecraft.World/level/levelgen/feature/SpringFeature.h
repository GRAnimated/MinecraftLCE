#pragma once

#include "Minecraft.World/level/levelgen/feature/Feature.h"

class Block;

class SpringFeature : public Feature {
public:
    SpringFeature(Block* block, bool unk);

    virtual bool place(Level* level, Random& random, const BlockPos& pos) override;

private:
    Block* mBlock;
};
