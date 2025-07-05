#pragma once

#include "net/minecraft/world/level/biome/Biome.h"

class SwampBiome : public Biome {
public:
    SwampBiome(EBiomeIDs id, BiomeProperties* properties);

    int getBaseClass() override;

    void* padding;
};
