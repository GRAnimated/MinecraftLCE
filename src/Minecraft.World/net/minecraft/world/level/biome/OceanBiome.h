#pragma once

#include "net/minecraft/world/level/biome/Biome.h"

class OceanBiome : public Biome {
public:
    OceanBiome(EBiomeIDs id, BiomeProperties* properties);
    ~OceanBiome() override = default;

    int getBaseClass() override;
    int getTemperatureCategory() override;
};
