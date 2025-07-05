#pragma once
#include "Minecraft.World/level/biome/Biome.h"

class MushroomIslandBiome : public Biome {
public:
    MushroomIslandBiome(EBiomeIDs id, BiomeProperties *properties);
    
    int getBaseClass() override;
};
