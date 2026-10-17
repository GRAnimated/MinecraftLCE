#pragma once

#include "net/minecraft/core/BlockPos.h"

class Level;
class Random;
class Biome;
class Feature;
class FlowerFeature;
class CustomizableSourceSettings;

class BiomeDecorator {
public:
    BiomeDecorator();
    virtual ~BiomeDecorator();
    virtual void decorate(Level*, Random&, Biome*, const BlockPos&);
    virtual void decorate(Biome*, Level*, Random&);
    virtual void decorateOres(Level*, Random&);

    void decorateDepthSpan(Level*, Random&, int count, Feature*, int minHeight, int maxHeight);
    void decorateDepthAverage(Level*, Random&, int count, Feature*, int centerHeight, int spread);

    bool m_decorating;
    BlockPos m_origin;
    CustomizableSourceSettings* m_settings;
    Feature* m_clay;
    Feature* m_sand;
    Feature* m_gravelPatch;
    Feature* m_dirt;
    Feature* m_gravel;
    Feature* m_granite;
    Feature* m_diorite;
    Feature* m_andesite;
    Feature* m_coal;
    Feature* m_iron;
    Feature* m_gold;
    Feature* m_redstone;
    Feature* m_diamond;
    Feature* m_lapis;
    FlowerFeature* m_flowers;
    Feature* m_brownMushrooms;
    Feature* m_redMushrooms;
    Feature* m_hugeMushrooms;
    Feature* m_reeds;
    Feature* m_cactus;
    Feature* m_waterlilies;
    int m_waterlilyCount;
    int m_treeCount;
    float m_extraTreeChance;
    int m_flowerCount;
    int m_grassCount;
    int m_deadBushCount;
    int m_mushroomCount;
    int m_reedCount;
    int m_cactusCount;
    int m_gravelPatchCount;
    int m_sandCount;
    int m_clayCount;
    int m_hugeMushroomCount;
    bool m_generateLiquids;
};

static_assert(sizeof(BiomeDecorator) == 0x100, "Switch biome decorator layout");
