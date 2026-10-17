#pragma once

#include "net/minecraft/world/level/biome/Biome.h"
#include "net/minecraft/world/level/biome/BiomeDecorator.h"
#include "types.h"

class MesaBiome : public Biome {
public:
    class MesaDecorator : public BiomeDecorator {
    public:
        MesaDecorator() = default;
        void decorateOres(Level*, Random&) override;
    };

    static LegacyBlockData COARSE_DIRT;
    static LegacyBlockData GRASS;
    static LegacyBlockData HARDENED_CLAY;
    static LegacyBlockData STAINED_HARDENED_CLAY;
    static LegacyBlockData ORANGE_CLAY;
    static LegacyBlockData RED_SAND;
    static void staticCtor();

    MesaBiome(EBiomeIDs id, bool bryce, bool forest, BiomeProperties* properties);
    ~MesaBiome() override;
    int getBaseClass() override;
    Feature* getTreeFeature(Random&) override;
    unsigned int getGrassColor(const BlockPos*) override;
    unsigned int getFoliageColor(const BlockPos*) override;
    void buildSurfaceAt(Level*, Random&, ChunkPrimer*, int, int, double) override;

    void generateBands(long long seed);
    LegacyBlockData getBand(int x, int y, int z);

    LegacyBlockData* m_clayBands;
    long long m_seed;
    PerlinSimplexNoise* m_pillarNoise;
    PerlinSimplexNoise* m_pillarRoofNoise;
    PerlinSimplexNoise* m_clayBandsOffsetNoise;
    bool m_bryce;
    bool m_forest;
};

ASSERT_SIZEOF(MesaBiome, 0x178)
