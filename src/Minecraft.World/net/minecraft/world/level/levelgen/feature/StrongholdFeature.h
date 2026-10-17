#pragma once

#include "net/minecraft/world/level/levelgen/feature/StructureFeature.h"

class StrongholdFeature : public StructureFeature {
public:
    std::wstring getFeatureName() override;
    BlockPos* getNearestGeneratedFeature(Level*, const BlockPos&, bool) override;
    bool isFeatureChunk(int, int, bool) override;
    StructureStart* createStructureStart(int, int) override;
    std::vector<BlockPos>* getGuesstimatedFeaturePositions() override;

    StrongholdFeature();

    char m_filler[0x48];
};

ASSERT_SIZEOF(StrongholdFeature, 0xB0)
