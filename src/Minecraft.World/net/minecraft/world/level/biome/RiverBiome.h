#pragma once

#include "net/minecraft/world/level/biome/Biome.h"

class RiverBiome : public Biome {
public:
    RiverBiome(EBiomeIDs id, BiomeProperties* properties);

    int getBaseClass() override;
};
