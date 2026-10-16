#pragma once

#include "net/minecraft/world/level/levelgen/feature/Feature.h"
#include "types.h"

class Block;

class DeadBushFeature : public Feature {
public:
    DeadBushFeature(Block*);
    ~DeadBushFeature() override = default;
    bool place(Level*, Random&, const BlockPos&) override;
};

ASSERT_SIZEOF(DeadBushFeature, 0x10)
