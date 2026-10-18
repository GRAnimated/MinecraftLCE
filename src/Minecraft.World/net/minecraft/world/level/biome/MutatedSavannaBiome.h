#pragma once

#include "net/minecraft/world/level/biome/SavannaBiome.h"

class MutatedSavannaBiome : public SavannaBiome {
public:
    MutatedSavannaBiome(EBiomeIDs id, BiomeProperties* properties);

    void buildSurfaceAt(Level*, Random&, ChunkPrimer*, int, int, double) override;
    void decorate(Level*, Random&, const BlockPos&) override;
};
