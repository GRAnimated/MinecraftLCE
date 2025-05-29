#pragma once

#include "Minecraft.World/ArrayWithLength.h"

class BlockPos;
class Biome;
class Random;

class BiomeSource {
public:
    virtual ~BiomeSource();
    virtual void getBiome(const BlockPos&);
    virtual void getBiome(const BlockPos&, Biome*);
    virtual void getRawBiomeBlock(arrayWithLength<Biome*>&, int, int, int, int) const;
    virtual void getRawBiomeIndices(arrayWithLength<int>&, int, int, int, int) const;
    virtual void getBiomeBlock(arrayWithLength<Biome*>&, int, int, int, int, bool) const;
    virtual void getBiomeIndexBlock(int, int, int, int) const;
    virtual void getBiomeIndexBlock(arrayWithLength<unsigned char>&, int, int, int, int, bool) const;
    virtual void containsOnly(int, int, int, std::vector<Biome*> const&);
    virtual void findBiome(int, int, int, std::vector<Biome*>, Random*);
    virtual void isFixedBiome();
    virtual void getFixedBiome();
};
