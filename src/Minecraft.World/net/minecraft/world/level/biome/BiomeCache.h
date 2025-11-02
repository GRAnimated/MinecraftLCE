#pragma once

#include "net/minecraft/world/ArrayWithLength.h"
#include <unordered_map>

class BiomeSource;
class Biome;

class BiomeCache {
public:
    class Area;

    BiomeCache(BiomeSource* biomeSource);
    ~BiomeCache();

    Biome* getBiome(int, int, Biome*);
    arrayWithLength<Biome*> getBiomeBlockAt(int, int);
    arrayWithLength<unsigned char> getBiomeIndexBlockAt(int, int);
    Area* getBlockAt(int, int);
    void update();

    BiomeSource* mBiomeSource;
    long long field_8;
    std::unordered_map<long long, Area*> field_10;
    std::vector<Area*> mSlots;
    uint8_t skip[0x20];
};

ASSERT_SIZEOF(BiomeCache, 0x70)
