#pragma once
#include "Minecraft.World/level/biome/Biome.h"

class DesertBiome : public Biome {
public:
    DesertBiome(EBiomeIDs id, BiomeProperties *properties);
    
    int getBaseClass() override;
};
