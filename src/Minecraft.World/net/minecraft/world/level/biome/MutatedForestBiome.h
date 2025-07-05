#pragma once
#include "net/minecraft/world/level/biome/Biome.h"

class MutatedForestBiome : public Biome {
public:
    MutatedForestBiome(EBiomeIDs id, BiomeProperties* properties);

    int getBaseClass() override;
};
