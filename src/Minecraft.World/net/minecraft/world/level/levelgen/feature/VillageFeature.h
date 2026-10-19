#pragma once

#include "net/minecraft/world/level/levelgen/feature/StructureFeature.h"
#include <vector>

class Biome;

class VillageFeature : public StructureFeature {
public:
    std::wstring getFeatureName() override;
    BlockPos* getNearestGeneratedFeature(Level*, const BlockPos&, bool) override;
    bool isFeatureChunk(int, int, bool) override;
    StructureStart* createStructureStart(int, int) override;

    VillageFeature(int);

    static void staticCtor();
    static std::vector<Biome*> ALLOWED_BIOMES;

    char m_filler[0x10];
};

ASSERT_SIZEOF(VillageFeature, 0x78)
