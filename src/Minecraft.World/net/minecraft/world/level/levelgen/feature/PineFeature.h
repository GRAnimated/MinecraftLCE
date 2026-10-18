#pragma once

#include "net/minecraft/world/level/levelgen/feature/AbstractTreeFeature.h"

class PineFeature : public AbstractTreeFeature {
public:
    PineFeature();
    static void staticCtor();
    bool place(Level*, Random&, const BlockPos&) override;

    static const BlockState* TRUNK;
    static const BlockState* LEAVES;
};

ASSERT_SIZEOF(PineFeature, 0x28)
