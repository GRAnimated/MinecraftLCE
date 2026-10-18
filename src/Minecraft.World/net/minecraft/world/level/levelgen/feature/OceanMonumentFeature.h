#pragma once

#include "net/minecraft/world/level/biome/Biome.h"
#include "net/minecraft/world/level/levelgen/feature/StructureFeature.h"

#include <vector>

class OceanMonumentFeature : public StructureFeature {
public:
    std::wstring getFeatureName() override;
    BlockPos* getNearestGeneratedFeature(Level*, const BlockPos&, bool) override;
    bool isFeatureChunk(int, int, bool) override;
    StructureStart* createStructureStart(int, int) override;

    static std::vector<Biome::MobSpawnerData*> MOB_SPAWNERS;

    OceanMonumentFeature();

    std::vector<Biome::MobSpawnerData*>* getEnemies();

    static void staticCtor();

    char m_filler[0x38];
};

ASSERT_SIZEOF(OceanMonumentFeature, 0xA0)
