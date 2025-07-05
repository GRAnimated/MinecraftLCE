#pragma once

#include "net/minecraft/world/level/biome/Biome.h"

class PlainsBiome : public Biome {
public:
    PlainsBiome(EBiomeIDs id, bool, BiomeProperties* properties);

    int getBaseClass() override;
};
