#pragma once

#include "net/minecraft/world/level/biome/Biome.h"

class BeachBiome : public Biome {
public:
    BeachBiome(EBiomeIDs id, BiomeProperties* properties);
    ~BeachBiome() override = default;

    int getBaseClass() override;
};
