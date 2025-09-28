#pragma once

#include "types.h"
#include "net/minecraft/world/level/biome/Biome.h"

class MesaBiome : public Biome {
public:
    MesaBiome(EBiomeIDs id, bool, bool, BiomeProperties* properties);

    int getBaseClass() override;

    char padding[0x30];
};

ASSERT_SIZEOF(MesaBiome, 0x178)
