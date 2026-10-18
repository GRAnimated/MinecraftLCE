#pragma once

#include "net/minecraft/world/level/levelgen/feature/Feature.h"
#include "types.h"

class FossilFeature : public Feature {
public:
    FossilFeature() = default;
    ~FossilFeature() override = default;
    bool place(Level*, Random&, const BlockPos&) override;
};

ASSERT_SIZEOF(FossilFeature, 0x10)
