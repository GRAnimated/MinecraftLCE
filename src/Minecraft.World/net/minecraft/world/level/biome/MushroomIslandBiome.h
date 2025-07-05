#pragma once
#include "net/minecraft/world/level/biome/Biome.h"

class MushroomIslandBiome : public Biome {
public:
    MushroomIslandBiome(EBiomeIDs id, BiomeProperties* properties);

    int getBaseClass() override;
};
