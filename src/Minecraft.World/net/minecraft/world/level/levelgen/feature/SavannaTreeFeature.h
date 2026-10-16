#pragma once

#include "net/minecraft/world/level/levelgen/feature/AbstractTreeFeature.h"

class SavannaTreeFeature : public AbstractTreeFeature {
public:
    static const BlockState* TRUNK;
    static const BlockState* LEAVES;
    SavannaTreeFeature(bool update);
    ~SavannaTreeFeature() override;
    bool place(Level*, Random&, const BlockPos&) override;
    static void staticCtor();
    void placeLogAt(Level*, const BlockPos&);
    void placeLeafAt(Level*, const BlockPos&);
};

ASSERT_SIZEOF(SavannaTreeFeature, 0x28)
