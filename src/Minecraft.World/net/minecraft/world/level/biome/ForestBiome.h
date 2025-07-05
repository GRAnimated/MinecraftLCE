#pragma once

#include "net/minecraft/world/level/biome/Biome.h"

class ForestBiome : public Biome {
public:
    enum EType { DEFAULT = 0, FLOWER = 1, BIRCH = 2, ROOFED = 3 };

    ForestBiome(EBiomeIDs id, EType type, BiomeProperties* properties);

    int getBaseClass() override;
};
