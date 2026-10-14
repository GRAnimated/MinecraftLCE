#pragma once

#include "net/minecraft/world/level/levelgen/feature/AbstractTreeFeature.h"

class Direction;
class MutableBlockPos;

class TreeFeature : public AbstractTreeFeature {
public:
    static void staticCtor();
    TreeFeature(bool update);
    TreeFeature(bool update, int minHeight, const BlockState* trunk, const BlockState* leaves, bool vines);
    bool place(Level*, Random&, const BlockPos&) override;

    bool prepareSpawn(Level*, const BlockPos&, int height);
    void placeLeaf(Level*, const MutableBlockPos&);
    void addHangingVine(Level*, const BlockPos&, const BooleanProperty*);
    void placeCocoa(Level*, int age, const BlockPos&, const Direction*);

    static const BlockState* TRUNK;
    static const BlockState* LEAVES;
};

ASSERT_SIZEOF(TreeFeature, 0x28)
