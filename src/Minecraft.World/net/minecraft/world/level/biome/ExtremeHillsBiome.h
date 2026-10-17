#pragma once

#include "net/minecraft/world/level/biome/Biome.h"

class OreFeature;

class ExtremeHillsBiome : public Biome {
public:
    enum EType { DEFAULT = 0, EDGE = 1, M = 2 };

    ExtremeHillsBiome(EBiomeIDs id, EType type, BiomeProperties* properties);
    ~ExtremeHillsBiome() override;

    int getBaseClass() override;
    Feature* getTreeFeature(Random&) override;
    void decorate(Level*, Random&, const BlockPos&) override;
    void buildSurfaceAt(Level*, Random&, ChunkPrimer*, int, int, double) override;

private:
    OreFeature* m_oreFeature;
    EType m_type;
};

ASSERT_SIZEOF(ExtremeHillsBiome, 0x158)
