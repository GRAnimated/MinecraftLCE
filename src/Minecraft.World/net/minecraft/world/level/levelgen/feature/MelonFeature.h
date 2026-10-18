#pragma once

#include "net/minecraft/world/level/levelgen/feature/Feature.h"

class MelonFeature : public Feature {
public:
    MelonFeature();
    ~MelonFeature() override;
    bool place(Level*, Random&, const BlockPos&) override;
};
