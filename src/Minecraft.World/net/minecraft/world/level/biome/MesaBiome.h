#pragma once
#include "net/minecraft/world/level/biome/Biome.h"

class MesaBiome : public Biome {
public:
    MesaBiome(EBiomeIDs id, bool, bool, BiomeProperties* properties);

    int getBaseClass() override;

    char padding[0x30];
};

static_assert(sizeof(MesaBiome) == 0x178);
