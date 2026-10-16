#pragma once

#include "net/minecraft/world/level/levelgen/feature/AbstractTreeFeature.h"

class SavannaTreeFeature : public AbstractTreeFeature {
public:
    SavannaTreeFeature(bool update);
    bool place(Level*, Random&, const BlockPos&) override;
    static void staticCtor();
};

ASSERT_SIZEOF(SavannaTreeFeature, 0x28)
