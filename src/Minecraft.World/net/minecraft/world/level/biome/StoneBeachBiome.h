#pragma once

#include "net/minecraft/world/level/biome/Biome.h"

class StoneBeachBiome : public Biome {
public:
    StoneBeachBiome(EBiomeIDs id, BiomeProperties* properties);
    ~StoneBeachBiome() override = default;

    int getBaseClass() override;
};
