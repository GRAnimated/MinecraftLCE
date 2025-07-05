#pragma once
#include "net/minecraft/world/level/biome/Biome.h"

class BeachBiome : public Biome {
public:
    BeachBiome(EBiomeIDs id, BiomeProperties* properties);

    int getBaseClass() override;
};
