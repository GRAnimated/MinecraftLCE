#pragma once

#include "net/minecraft/world/level/levelgen/feature/Feature.h"
#include "types.h"

class Block;

class SandFeature : public Feature {
public:
    SandFeature(Block*, int);
    ~SandFeature() override = default;
    bool place(Level*, Random&, const BlockPos&) override;

private:
    Block* m_block;
    int m_radius;
};

ASSERT_SIZEOF(SandFeature, 0x20)
