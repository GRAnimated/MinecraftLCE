#pragma once

#include "net/minecraft/world/level/levelgen/feature/Feature.h"

class Block;

class SpringFeature : public Feature {
public:
    SpringFeature(Block* block, bool unk);

    bool place(Level* level, Random& random, const BlockPos& pos) override;

private:
    Block* mBlock;
};

static_assert(sizeof(SpringFeature) == 0x18, "SpringFeature layout must match the Switch object");
