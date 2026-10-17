#pragma once

#include "net/minecraft/world/level/biome/ForestBiome.h"

class MutatedForestBiome : public ForestBiome {
public:
    MutatedForestBiome(EBiomeIDs id, BiomeProperties* properties);

    Feature* getTreeFeature(Random&) override;
};
