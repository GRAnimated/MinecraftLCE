#pragma once

#include "net/minecraft/world/level/levelgen/feature/StructureFeature.h"

class TheEndLevelSource;

// Constructor and specialized virtual methods remain unreconstructed.
class EndCityFeature : public StructureFeature {
public:
    std::wstring getFeatureName() override;
    BlockPos* getNearestGeneratedFeature(Level*, const BlockPos&, bool) override;
    bool isFeatureChunk(int, int, bool) override;
    StructureStart* createStructureStart(int, int) override;

    explicit EndCityFeature(TheEndLevelSource*);
    TheEndLevelSource* m_source;
};
ASSERT_SIZEOF(EndCityFeature, 0x70)
