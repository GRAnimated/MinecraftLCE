#pragma once

#include "net/minecraft/world/level/levelgen/feature/AbstractTreeFeature.h"

class SwampTreeFeature : public AbstractTreeFeature {
public:
    static const BlockState* TRUNK;
    static const BlockState* LEAVES;
    SwampTreeFeature();
    static void staticCtor();
    bool place(Level*, Random&, const BlockPos&) override;
    void addVine(Level*, const BlockPos&, const BooleanProperty*);
};

ASSERT_SIZEOF(SwampTreeFeature, 0x28)
