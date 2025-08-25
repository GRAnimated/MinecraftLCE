#pragma once

#include "net/minecraft/world/level/biome/Biome.h"
#include "net/minecraft/world/level/levelgen/feature/StructureFeature.h"

class BlockPos;

class RandomScatteredLargeFeature : public StructureFeature {
public:
    RandomScatteredLargeFeature();

    bool isSwamphut(const BlockPos&);
    std::vector<Biome::MobSpawnerData>* getSwamphutEnemies();

    char filler[0x20];
};

ASSERT_SIZEOF(RandomScatteredLargeFeature, 0x88)
