#pragma once

#include "net/minecraft/world/level/levelgen/feature/Feature.h"
#include "types.h"

class ReedsFeature : public Feature {
public:
    ReedsFeature() = default;
    ~ReedsFeature() override = default;
    bool place(Level*, Random&, const BlockPos&) override;
};

ASSERT_SIZEOF(ReedsFeature, 0x10)
