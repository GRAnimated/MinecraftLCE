#pragma once

#include "net/minecraft/world/level/biome/Biome.h"
#include "types.h"

class MesaBiome : public Biome {
public:
    MesaBiome(EBiomeIDs id, bool, bool, BiomeProperties* properties);

    int getBaseClass() override;

    char m_padding[0x30];
};

ASSERT_SIZEOF(MesaBiome, 0x178)
