#pragma once

#include "net/minecraft/world/level/biome/Biome.h"

class JungleBiome : public Biome {
public:
    enum EType { DEFAULT = 0, EDGE = 1 };

    JungleBiome(EBiomeIDs id, bool edge, BiomeProperties* properties);
    static void staticCtor();

    int getBaseClass() override;
    Feature* getTreeFeature(Random&) override;
    Feature* getGrassFeature(Random&) override;
    void decorate(Level*, Random&, const BlockPos&) override;

private:
    static const BlockState* TRUNK;
    static const BlockState* LEAVES;
    static const BlockState* BUSH_LEAVES;
    bool m_edge;
};

ASSERT_SIZEOF(JungleBiome, 0x148)
