#pragma once

#include "net/minecraft/world/level/levelgen/feature/Feature.h"

class VinesFeature : public Feature {
public:
    VinesFeature();
    bool place(Level*, Random&, const BlockPos&) override;
};
