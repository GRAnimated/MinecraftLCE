#pragma once

#include "net/minecraft/world/level/levelgen/feature/MegaTreeFeature.h"

class MegaPineTreeFeature : public MegaTreeFeature {
public:
    MegaPineTreeFeature(bool update, bool useBaseHeight);
    static void staticCtor();
    bool place(Level*, Random&, const BlockPos&) override;

private:
    bool m_useBaseHeight;
};

ASSERT_SIZEOF(MegaPineTreeFeature, 0x30)
