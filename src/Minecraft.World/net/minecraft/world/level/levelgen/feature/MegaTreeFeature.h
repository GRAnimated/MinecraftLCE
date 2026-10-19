#pragma once

#include "net/minecraft/world/level/levelgen/feature/AbstractTreeFeature.h"

class MegaTreeFeature : public AbstractTreeFeature {
public:
    MegaTreeFeature(bool update, int minHeight, int heightRange, const BlockState*, const BlockState*);
    virtual int calcTreeHeigth(Random&);
    virtual bool prepareTree(Level*, Random&, const BlockPos&, int);
    virtual void placeDoubleTrunkLeaves(Level*, const BlockPos&, int);
    virtual void placeSingleTrunkLeaves(Level*, const BlockPos&, int);
    bool checkIsFree(Level*, const BlockPos&, int);
    bool makeDirtFloor(const BlockPos&, Level*);

protected:
    int m_heightRange;
};

ASSERT_SIZEOF(MegaTreeFeature, 0x30)
