#pragma once

#include "net/minecraft/world/level/levelgen/feature/Feature.h"

class Block;

class HellSpringFeature : public Feature {
public:
    HellSpringFeature(Block* block, bool unk);

    virtual bool place(Level* level, Random& random, const BlockPos& pos) override;

private:
    Block* mBlock;
    bool mIsForcePlacement;
};
