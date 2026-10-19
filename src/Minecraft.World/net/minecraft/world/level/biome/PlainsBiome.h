#pragma once

#include "net/minecraft/world/level/biome/Biome.h"

class PlainsBiome : public Biome {
public:
    PlainsBiome(EBiomeIDs id, bool, BiomeProperties* properties);
    ~PlainsBiome() override = default;

    int getBaseClass() override;
    Feature* getTreeFeature(Random&) override;
    FlowerBlock::Flower* getRandomFlower(Random&, const BlockPos*) override;
    void decorate(Level*, Random&, const BlockPos&) override;

private:
    bool m_sunflowers;
};

ASSERT_SIZEOF(PlainsBiome, 0x148)
