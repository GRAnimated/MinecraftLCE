#pragma once

#include "net/minecraft/world/level/biome/Biome.h"
#include "net/minecraft/world/level/levelgen/feature/StructureFeature.h"

class NetherBridgeFeature : public StructureFeature {
public:
    std::wstring getFeatureName() override;
    BlockPos* getNearestGeneratedFeature(Level*, const BlockPos&, bool) override;
    bool isFeatureChunk(int, int, bool) override;
    StructureStart* createStructureStart(int, int) override;

    NetherBridgeFeature();
    ~NetherBridgeFeature() override;
    std::vector<Biome::MobSpawnerData*>* getSpawnList();

private:
    // Structure-owned spawn data and trailing state are still external reconstruction work.
    char m_unknown68[0x28];
};

ASSERT_SIZEOF(NetherBridgeFeature, 0x90)
