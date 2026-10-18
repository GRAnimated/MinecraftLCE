#pragma once

#include "net/minecraft/world/level/biome/Biome.h"

class ForestBiome : public Biome {
public:
    enum EType { DEFAULT = 0, FLOWER = 1, BIRCH = 2, ROOFED = 3 };

    ForestBiome(EBiomeIDs id, EType type, BiomeProperties* properties);
    ~ForestBiome() override = default;

    int getBaseClass() override;
    Feature* getTreeFeature(Random&) override;
    FlowerBlock::Flower* getRandomFlower(Random&, const BlockPos*) override;
    unsigned int getGrassColor(const BlockPos*) override;
    void decorate(Level*, Random&, const BlockPos&) override;
    void addMushrooms(Level*, Random&, const BlockPos&);
    void addDoublePlants(Level*, Random&, const BlockPos&, int);

private:
    EType m_type;
};

ASSERT_SIZEOF(ForestBiome, 0x148)
