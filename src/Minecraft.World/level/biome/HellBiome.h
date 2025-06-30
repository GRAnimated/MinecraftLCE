#pragma once
#include "Minecraft.World/level/biome/Biome.h"

class HellBiome : public Biome {
public:
    HellBiome(EBiomeIDs id, BiomeProperties *properties);
    
    int getBaseClass() override;
};
