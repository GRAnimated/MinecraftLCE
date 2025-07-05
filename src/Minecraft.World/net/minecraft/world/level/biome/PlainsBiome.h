#pragma once
#include "Minecraft.World/level/biome/Biome.h"

class PlainsBiome : public Biome {
public:
    PlainsBiome(EBiomeIDs id, bool, BiomeProperties *properties);
    
    int getBaseClass() override;
};
