#pragma once
#include "net/minecraft/world/level/biome/Biome.h"

class VoidBiome : public Biome {
public:
    VoidBiome(EBiomeIDs id, BiomeProperties* properties);

    int getBaseClass() override;
};
