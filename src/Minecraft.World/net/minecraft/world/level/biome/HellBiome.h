#pragma once

#include "net/minecraft/world/level/biome/Biome.h"

class HellBiome : public Biome {
public:
    HellBiome(EBiomeIDs id, BiomeProperties* properties);
    ~HellBiome() override = default;

    int getBaseClass() override;
    unsigned int getSkyColor(float) override;
    Vec3* getFogColor(float, float) const override;
    bool isFoggy() override;
    bool isNatural() override;
};
