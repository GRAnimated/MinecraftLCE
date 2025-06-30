#pragma once
#include "Minecraft.World/level/biome/Biome.h"

class IceBiome : public Biome {
public:
    enum EType {
        DEFAULT = 0,
        SPIKES = 1
    };

    IceBiome(EBiomeIDs id, EType type, BiomeProperties *properties);
    
    int getBaseClass() override;

    char padding[0x10];
};

static_assert(sizeof(IceBiome) == 0x158);
