#include "net/minecraft/world/level/biome/FixedBiomeSource.h"

#include "NX/Platform.h"
#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/biome/Biome.h"
#include <algorithm>

// Shared fill routines retain their original array-by-value calling convention.
void fillFixedBiomePointers(arrayWithLength<Biome*> array, unsigned int from, unsigned int to, Biome* value) {
    std::fill(array.m_data + from, array.m_data + to, value);
}

void fillFixedBiomeIndices(arrayWithLength<unsigned char> array, unsigned int from, unsigned int to,
                           int value) {
    std::fill(array.m_data + from, array.m_data + to, static_cast<unsigned char>(value));
}

FixedBiomeSource::FixedBiomeSource(Biome* biome) : m_biome(biome) {}

Biome* FixedBiomeSource::getBiome(const BlockPos&) {
    return m_biome;
}
bool FixedBiomeSource::isFixedBiome() {
    return true;
}
Biome* FixedBiomeSource::getFixedBiome() {
    return m_biome;
}

void FixedBiomeSource::getBiomeBlock(arrayWithLength<Biome*>& biomes, int, int, int width, int depth,
                                     bool) const {
    MemSect(36);
    biomes.resize(width * depth);
    MemSect(0);
    fillFixedBiomePointers(biomes, 0, width * depth, m_biome);
}

void FixedBiomeSource::getRawBiomeBlock(arrayWithLength<Biome*>& biomes, int, int, int width,
                                        int depth) const {
    MemSect(36);
    biomes.resize(width * depth);
    MemSect(0);
    fillFixedBiomePointers(biomes, 0, width * depth, m_biome);
}

void FixedBiomeSource::getBiomeIndexBlock(arrayWithLength<unsigned char>& biomes, int, int, int width,
                                          int depth, bool) const {
    MemSect(36);
    biomes.resize(width * depth);
    MemSect(0);
    int biomeId = m_biome->m_biomeId;
    fillFixedBiomeIndices(biomes, 0, width * depth, biomeId);
}

bool FixedBiomeSource::containsOnly(int, int, int, const std::vector<Biome*>& biomes) {
    return std::find(biomes.begin(), biomes.end(), m_biome) != biomes.end();
}

BlockPos* FixedBiomeSource::findBiome(int x, int z, int radius, std::vector<Biome*> biomes, Random* random) {
    if (std::find(biomes.begin(), biomes.end(), m_biome) == biomes.end())
        return nullptr;
    return new BlockPos(x - radius + random->nextInt(radius * 2 + 1), 0,
                        z - radius + random->nextInt(radius * 2 + 1));
}
