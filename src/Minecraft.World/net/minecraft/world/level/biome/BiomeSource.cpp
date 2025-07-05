#include "net/minecraft/world/level/biome/BiomeSource.h"

Biome* BiomeSource::getBiome(const BlockPos &pos) {
    return this->getBiome(pos, nullptr);
}

bool BiomeSource::isFixedBiome() {
    return false;
}

void *BiomeSource::getFixedBiome() {
    return nullptr;
}