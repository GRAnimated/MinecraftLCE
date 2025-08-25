#pragma once

#include "net/minecraft/world/level/biome/Biome.h"
#include "net/minecraft/world/level/levelgen/feature/StructureFeature.h"

#include <vector>

class OceanMonumentFeature : public StructureFeature {
public:
    static std::vector<Biome::MobSpawnerData> MOB_SPAWNERS;

    OceanMonumentFeature();

    std::vector<Biome::MobSpawnerData>* getEnemies();

    char filler[0x38];
};

ASSERT_SIZEOF(OceanMonumentFeature, 0xA0)
