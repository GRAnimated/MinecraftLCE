#pragma once

#include "net/minecraft/world/level/biome/Biome.h"

class SwampBiome : public Biome {
public:
    SwampBiome(EBiomeIDs id, BiomeProperties* properties);
    ~SwampBiome() override = default;

    int getBaseClass() override;
    Feature* getTreeFeature(Random&) override;
    FlowerBlock::Flower* getRandomFlower(Random&, const BlockPos*) override;
    unsigned int getGrassColor(const BlockPos*) override;
    unsigned int getFoliageColor(const BlockPos*) override;
    void decorate(Level*, Random&, const BlockPos&) override;
    void buildSurfaceAt(Level*, Random&, ChunkPrimer*, int, int, double) override;

    static LegacyBlockData WATERLILY;

    void* m_padding;
};
