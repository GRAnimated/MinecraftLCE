#pragma once
#include "Minecraft.World/level/biome/Biome.h"

class VoidBiome : public Biome {
public:
    VoidBiome(EBiomeIDs id, BiomeProperties *properties);
    
    int getBaseClass() override;
};
