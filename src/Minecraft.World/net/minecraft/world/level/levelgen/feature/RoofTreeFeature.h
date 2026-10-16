#pragma once

#include "net/minecraft/world/level/levelgen/feature/AbstractTreeFeature.h"

class RoofTreeFeature : public AbstractTreeFeature {
public:
    RoofTreeFeature(bool);
    static void staticCtor();
    bool place(Level*, Random&, const BlockPos&) override;
};

ASSERT_SIZEOF(RoofTreeFeature, 0x28)
