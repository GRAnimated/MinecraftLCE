#pragma once

#include "net/minecraft/world/level/levelgen/feature/Feature.h"
#include "types.h"

class Block;

class BlockBlobFeature : public Feature {
public:
    BlockBlobFeature(Block*, int);
    ~BlockBlobFeature() override;
    bool place(Level*, Random&, const BlockPos&) override;

private:
    Block* m_block;
    int m_radius;
};

ASSERT_SIZEOF(BlockBlobFeature, 0x20)
