#pragma once

#include "net/minecraft/world/level/levelgen/feature/Feature.h"

class Block;

class HellSpringFeature : public Feature {
public:
    HellSpringFeature(Block* block, bool unk);

    bool place(Level* level, Random& random, const BlockPos& pos) override;

private:
    Block* m_block;
    bool m_isForcePlacement;
};
