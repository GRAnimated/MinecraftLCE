#pragma once

#include "net/minecraft/world/level/levelgen/feature/AbstractTreeFeature.h"

class RoofTreeFeature : public AbstractTreeFeature {
public:
    static const BlockState* TRUNK;
    static const BlockState* LEAVES;
    RoofTreeFeature(bool);
    ~RoofTreeFeature() override;
    static void staticCtor();
    bool place(Level*, Random&, const BlockPos&) override;
    bool canPlaceTreeOfHeight(Level*, const BlockPos&, int);
    void placeLogAt(Level*, const BlockPos&);
    void placeLeafAt(Level*, int, int, int);
};

ASSERT_SIZEOF(RoofTreeFeature, 0x28)
