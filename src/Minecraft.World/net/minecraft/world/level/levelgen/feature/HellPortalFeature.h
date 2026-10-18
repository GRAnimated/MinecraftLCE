#pragma once

#include "net/minecraft/world/level/levelgen/feature/Feature.h"

class HellPortalFeature : public Feature {
public:
    HellPortalFeature() = default;
    bool place(Level*, Random&, const BlockPos&) override;
};
