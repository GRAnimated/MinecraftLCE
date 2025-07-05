#pragma once
#include "Minecraft.World/level/biome/Biome.h"

class TheEndBiome : public Biome {
public:
    TheEndBiome(EBiomeIDs id, BiomeProperties *properties);
    
    int getBaseClass() override;
};
