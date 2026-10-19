#pragma once

#include "net/minecraft/world/level/biome/Biome.h"

class MushroomIslandBiome : public Biome {
public:
    MushroomIslandBiome(EBiomeIDs id, BiomeProperties* properties);
    ~MushroomIslandBiome() override = default;

    int getBaseClass() override;
};
