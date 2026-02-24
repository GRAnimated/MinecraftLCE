#pragma once

#include "net/minecraft/world/level/levelgen/feature/Feature.h"

class Block;

class ClayFeature : public Feature {
public:
    ClayFeature(int unk);

    bool place(Level* level, Random& random, const BlockPos& pos) override;

private:
    Block* m_block;
    int m_field18;
};
