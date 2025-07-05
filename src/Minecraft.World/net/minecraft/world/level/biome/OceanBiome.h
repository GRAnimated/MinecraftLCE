#pragma once
#include "net/minecraft/world/level/biome/Biome.h"

class OceanBiome : public Biome {
public:
    OceanBiome(EBiomeIDs id, BiomeProperties* properties);

    int getBaseClass() override;
};
