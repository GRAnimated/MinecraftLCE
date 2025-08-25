#pragma once

#include "net/minecraft/world/ArrayWithLength.h"

class BlockPos;
class Biome;
class Random;

class BiomeSource {
public:
    class LayerOverrideSettings;

    virtual ~BiomeSource();
    virtual Biome* getBiome(const BlockPos&);
    virtual Biome* getBiome(const BlockPos&, Biome*);
    virtual void getRawBiomeBlock(arrayWithLength<Biome*>&, int, int, int, int) const;
    virtual void getRawBiomeIndices(arrayWithLength<int>&, int, int, int, int) const;
    virtual void getBiomeBlock(arrayWithLength<Biome*>&, int, int, int, int, bool) const;
    virtual void getBiomeIndexBlock(int, int, int, int) const;
    virtual void getBiomeIndexBlock(arrayWithLength<unsigned char>&, int, int, int, int, bool) const;
    virtual void containsOnly(int, int, int, const std::vector<Biome*>&);
    virtual void findBiome(int, int, int, std::vector<Biome*>, Random*);
    virtual bool isFixedBiome();
    virtual void* getFixedBiome();

    class LayerOverrideSettings {
    public:
        bool GetBiomeScale();
        int GetCentreXChunk();
        int GetCentreZChunk();
    };
};
