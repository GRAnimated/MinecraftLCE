#pragma once

#include "net/minecraft/world/level/levelgen/feature/AbstractTreeFeature.h"

class SwampTreeFeature : public AbstractTreeFeature {
public:
    SwampTreeFeature();
    static void staticCtor();
    bool place(Level*, Random&, const BlockPos&) override;
};

ASSERT_SIZEOF(SwampTreeFeature, 0x28)
