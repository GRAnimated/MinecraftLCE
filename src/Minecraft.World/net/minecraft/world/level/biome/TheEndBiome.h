#pragma once

#include "net/minecraft/world/level/biome/Biome.h"

class TheEndBiome : public Biome {
public:
    TheEndBiome(EBiomeIDs id, BiomeProperties* properties);
    ~TheEndBiome() override = default;

    int getBaseClass() override;
    unsigned int getSkyColor(float) override;
    Vec3* getFogColor(float, float) const override;
    bool isNatural() override;
};
