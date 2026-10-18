#pragma once

#include "net/minecraft/world/level/levelgen/feature/Feature.h"

class EndIslandFeature : public Feature {
public:
    EndIslandFeature();
    ~EndIslandFeature() override = default;
    bool place(Level*, Random&, const BlockPos&) override;
};
