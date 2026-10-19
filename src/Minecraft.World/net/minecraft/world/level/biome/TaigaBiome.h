#pragma once

#include "net/minecraft/world/level/biome/Biome.h"

class TaigaBiome : public Biome {
public:
    enum EType { DEFAULT = 0, MEGA = 1, MEGA_SPRUCE = 2 };

    TaigaBiome(EBiomeIDs id, EType type, BiomeProperties* properties);
    ~TaigaBiome() override = default;

    int getBaseClass() override;
    Feature* getTreeFeature(Random&) override;
    Feature* getGrassFeature(Random&) override;
    void decorate(Level*, Random&, const BlockPos&) override;
    void buildSurfaceAt(Level*, Random&, ChunkPrimer*, int, int, double) override;

private:
    EType m_type;
};

ASSERT_SIZEOF(TaigaBiome, 0x148)
