#pragma once

#include "Minecraft.World/level/levelgen/feature/Feature.h"

class Block;

class ClayFeature : public Feature {
public:
    ClayFeature(int unk);

    virtual bool place(Level* level, Random& random, const BlockPos& pos) override;

private:
    Block* mBlock;
    int field_18;
};
