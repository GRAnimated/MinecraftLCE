#pragma once

#include "net/minecraft/world/level/biome/Biome.h"

class TheEndBiome : public Biome {
public:
    TheEndBiome(EBiomeIDs id, BiomeProperties* properties);

    int getBaseClass() override;
};
