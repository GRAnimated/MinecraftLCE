#pragma once

#include "net/minecraft/world/level/levelgen/feature/MegaTreeFeature.h"

class MegaPineTreeFeature : public MegaTreeFeature {
public:
    static const BlockState* TRUNK;
    static const BlockState* LEAVES;
    static const BlockState* PODZOL;
    MegaPineTreeFeature(bool update, bool useBaseHeight);
    ~MegaPineTreeFeature() override;
    static void staticCtor();
    bool place(Level*, Random&, const BlockPos&) override;
    void postPlaceTree(Level*, Random&, const BlockPos&) override;
    void createCrown(Level*, int x, int z, int y, int radius, Random&);
    void placePodzolAt(Level*, const BlockPos&);
    void placePodzolCircle(Level*, const BlockPos&);

private:
    bool m_useBaseHeight;
};

ASSERT_SIZEOF(MegaPineTreeFeature, 0x30)
