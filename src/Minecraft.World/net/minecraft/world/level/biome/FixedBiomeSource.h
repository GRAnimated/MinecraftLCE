#pragma once

#include "net/minecraft/world/level/biome/BiomeSource.h"
#include "types.h"

class FixedBiomeSource : public BiomeSource {
public:
    explicit FixedBiomeSource(Biome*);
    Biome* getBiome(const BlockPos&) override;
    void getRawBiomeBlock(arrayWithLength<Biome*>&, int, int, int, int) const override;
    void getBiomeBlock(arrayWithLength<Biome*>&, int, int, int, int, bool) const override;
    void getBiomeIndexBlock(arrayWithLength<unsigned char>&, int, int, int, int, bool) const override;
    bool containsOnly(int, int, int, const std::vector<Biome*>&) override;
    BlockPos* findBiome(int, int, int, std::vector<Biome*>, Random*) override;
    bool isFixedBiome() override;
    Biome* getFixedBiome() override;

private:
    Biome* m_biome;
};

ASSERT_SIZEOF(FixedBiomeSource, 0x88)
