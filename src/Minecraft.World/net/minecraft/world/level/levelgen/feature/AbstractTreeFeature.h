#pragma once

#include "net/minecraft/world/level/levelgen/feature/Feature.h"
#include "types.h"

class Block;
class BooleanProperty;

class AbstractTreeFeature : public Feature {
public:
    AbstractTreeFeature(bool update, int minHeight, const BlockState* trunk, const BlockState* leaves,
                        bool vines);
    virtual void postPlaceTree(Level*, Random&, const BlockPos&);

    bool isFree(Block*);
    void setDirtAt(Level*, const BlockPos&);
    void addVine(Level*, const BlockPos&, const BooleanProperty*);
    bool placeTrunk(Level*, const BlockPos&, Random&, int height);
    void placeFallenTrunk(Level*, const BlockPos&, Random&, int height);

protected:
    int m_minHeight;
    bool m_vines;
    const BlockState* m_trunk;
    const BlockState* m_leaves;
};

ASSERT_SIZEOF(AbstractTreeFeature, 0x28)
