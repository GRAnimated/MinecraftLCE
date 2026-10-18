#pragma once

#include "net/minecraft/world/level/levelgen/feature/StructureFeature.h"

class MineShaftFeature : public StructureFeature {
public:
    std::wstring getFeatureName() override;
    BlockPos* getNearestGeneratedFeature(Level*, const BlockPos&, bool) override;
    bool isFeatureChunk(int, int, bool) override;
    StructureStart* createStructureStart(int, int) override;

    MineShaftFeature();

    char m_filler[0x8];
};

ASSERT_SIZEOF(MineShaftFeature, 0x70)
