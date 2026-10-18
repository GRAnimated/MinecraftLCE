#pragma once

#include "net/minecraft/world/level/levelgen/feature/TreeFeature.h"

class GroundBushFeature : public TreeFeature {
public:
    GroundBushFeature(const BlockState* trunk, const BlockState* leaves);
    bool place(Level*, Random&, const BlockPos&) override;

private:
    const BlockState* m_bushLeaves;
    const BlockState* m_bushTrunk;
};
