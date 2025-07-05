#pragma once
#include "net/minecraft/world/level/biome/Biome.h"

class HellBiome : public Biome {
public:
    HellBiome(EBiomeIDs id, BiomeProperties* properties);

    int getBaseClass() override;
};
