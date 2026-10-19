#pragma once

#include "net/minecraft/world/level/levelgen/feature/AbstractTreeFeature.h"

class SpruceFeature : public AbstractTreeFeature {
public:
    SpruceFeature(bool update);
    static void staticCtor();
    bool place(Level*, Random&, const BlockPos&) override;

    static const BlockState* TRUNK;
    static const BlockState* LEAVES;
};

ASSERT_SIZEOF(SpruceFeature, 0x28)
