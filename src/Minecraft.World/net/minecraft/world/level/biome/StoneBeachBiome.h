#pragma once

#include "net/minecraft/world/level/biome/Biome.h"

class StoneBeachBiome : public Biome {
public:
    StoneBeachBiome(EBiomeIDs id, BiomeProperties* properties);

    int getBaseClass() override;
};
