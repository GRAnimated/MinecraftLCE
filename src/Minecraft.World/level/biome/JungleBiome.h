#pragma once
#include "Minecraft.World/level/biome/Biome.h"

class JungleBiome : public Biome {
public:
    enum EType {
        DEFAULT = 0,
        EDGE = 1
    };

    JungleBiome(EBiomeIDs id, EType type, BiomeProperties *properties);
    
    int getBaseClass() override;
};
