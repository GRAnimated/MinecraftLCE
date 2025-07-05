#pragma once
#include "Minecraft.World/level/biome/Biome.h"

class BeachBiome : public Biome {
public:
    BeachBiome(EBiomeIDs id, BiomeProperties *properties);
    
    int getBaseClass() override;
};
