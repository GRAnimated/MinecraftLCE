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

    BiomeSource* m_biomeSource;
    long long m_field8;
    std::unordered_map<long long, Area*> m_field10;
    std::vector<Area*> m_slots;
    uint8_t m_skip[0x20];
};

ASSERT_SIZEOF(BiomeCache, 0x70)
