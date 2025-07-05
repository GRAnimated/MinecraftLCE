#pragma once
#include "Minecraft.World/level/biome/Biome.h"

class OceanBiome : public Biome {
public:
    OceanBiome(EBiomeIDs id, BiomeProperties *properties);

    int getBaseClass() override;
};
