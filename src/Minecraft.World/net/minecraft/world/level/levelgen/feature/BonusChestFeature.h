#pragma once

#include "net/minecraft/world/level/levelgen/feature/Feature.h"

class BonusChestFeature : public Feature {
public:
    BonusChestFeature();
    bool place(Level*, Random&, const BlockPos&) override;
    bool place(Level*, Random&, const BlockPos&, bool fixedPosition);
};
