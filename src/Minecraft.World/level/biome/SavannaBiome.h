#pragma once
#include "Minecraft.World/level/biome/Biome.h"

class SavannaBiome : public Biome {
public:
    SavannaBiome(EBiomeIDs id, BiomeProperties *properties);
    
    int getBaseClass() override;
};
