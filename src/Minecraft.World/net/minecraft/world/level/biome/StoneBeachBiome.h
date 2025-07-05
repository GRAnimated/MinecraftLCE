#pragma once
#include "Minecraft.World/level/biome/Biome.h"

class StoneBeachBiome : public Biome {
public:
    StoneBeachBiome(EBiomeIDs id, BiomeProperties *properties);
    
    int getBaseClass() override;
};
