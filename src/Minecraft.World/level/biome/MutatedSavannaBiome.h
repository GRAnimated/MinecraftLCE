#pragma once
#include "Minecraft.World/level/biome/Biome.h"

class MutatedSavannaBiome : public Biome {
public:
    MutatedSavannaBiome(EBiomeIDs id, BiomeProperties *properties);
    
    int getBaseClass() override;
};
