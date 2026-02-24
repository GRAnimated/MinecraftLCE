#pragma once

#include "net/minecraft/world/level/biome/Biome.h"

class IceBiome : public Biome {
public:
    enum EType { DEFAULT = 0, SPIKES = 1 };

    IceBiome(EBiomeIDs id, EType type, BiomeProperties* properties);

    int getBaseClass() override;

    char m_padding[0x10];
};

ASSERT_SIZEOF(IceBiome, 0x158)
