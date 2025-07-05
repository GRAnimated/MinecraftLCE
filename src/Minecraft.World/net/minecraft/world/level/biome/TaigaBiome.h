#pragma once
#include "net/minecraft/world/level/biome/Biome.h"

class TaigaBiome : public Biome {
public:
    enum EType { DEFAULT = 0, MEGA = 1, MEGA_SPRUCE = 2 };

    TaigaBiome(EBiomeIDs id, EType type, BiomeProperties* properties);

    int getBaseClass() override;
};
