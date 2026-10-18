#pragma once

#include "net/minecraft/world/level/levelgen/feature/Feature.h"
#include "types.h"

class CactusFeature : public Feature {
public:
    CactusFeature() = default;
    ~CactusFeature() override = default;
    bool place(Level*, Random&, const BlockPos&) override;
};

ASSERT_SIZEOF(CactusFeature, 0x10)
