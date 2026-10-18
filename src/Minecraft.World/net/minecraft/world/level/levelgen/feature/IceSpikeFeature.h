#pragma once

#include "net/minecraft/world/level/levelgen/feature/Feature.h"

class IceSpikeFeature : public Feature {
public:
    IceSpikeFeature() = default;
    bool place(Level*, Random&, const BlockPos&) override;
};
