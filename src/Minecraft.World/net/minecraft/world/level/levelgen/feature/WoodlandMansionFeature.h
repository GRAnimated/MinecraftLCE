#pragma once

#include "net/minecraft/world/level/levelgen/feature/StructureFeature.h"

class GenericOverworldLevelSource;
class SuperflatConfig;

class WoodlandMansionFeature : public StructureFeature {
public:
    std::wstring getFeatureName() override;
    BlockPos* getNearestGeneratedFeature(Level*, const BlockPos&, bool) override;
    bool isFeatureChunk(int, int, bool) override;
    StructureStart* createStructureStart(int, int) override;

    WoodlandMansionFeature(GenericOverworldLevelSource*);
    WoodlandMansionFeature(GenericOverworldLevelSource*, SuperflatConfig*);

    static void staticCtor();

    char m_filler[0x40];
};

ASSERT_SIZEOF(WoodlandMansionFeature, 0xA8)
