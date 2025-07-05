#pragma once

#include "net/minecraft/world/level/biome/Biome.h"

class MutatedSavannaBiome : public Biome {
public:
    MutatedSavannaBiome(EBiomeIDs id, BiomeProperties* properties);

    int getBaseClass() override;
};
