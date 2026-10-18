#pragma once

#include "net/minecraft/world/level/biome/Biome.h"
#include "net/minecraft/world/level/levelgen/feature/StructureFeature.h"

class BlockPos;

class RandomScatteredLargeFeature : public StructureFeature {
public:
    std::wstring getFeatureName() override;
    BlockPos* getNearestGeneratedFeature(Level*, const BlockPos&, bool) override;
    bool isFeatureChunk(int, int, bool) override;
    StructureStart* createStructureStart(int, int) override;

    RandomScatteredLargeFeature();

    bool isSwamphut(const BlockPos&);
    std::vector<Biome::MobSpawnerData*>* getSwamphutEnemies();

    static void staticCtor();

    char m_filler[0x20];
};

ASSERT_SIZEOF(RandomScatteredLargeFeature, 0x88)
