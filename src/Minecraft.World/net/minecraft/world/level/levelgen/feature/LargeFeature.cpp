#include "net/minecraft/world/level/levelgen/feature/LargeFeature.h"

#include "net/minecraft/world/level/Level.h"

LargeFeature::LargeFeature() {
    m_radius = 8;
    m_random = Random();
}

LargeFeature::~LargeFeature() = default;

void LargeFeature::apply(Level* level, int chunkX, int chunkZ, ChunkPrimer* primer) {
    int radius = m_radius;
    m_level = level;
    m_random.setSeed(level->getSeed());
    long long seedX = m_random.nextLong();
    long long seedZ = m_random.nextLong();

    for (int sourceX = chunkX - radius; sourceX <= chunkX + radius; sourceX++) {
        for (int sourceZ = chunkZ - radius; sourceZ <= chunkZ + radius; sourceZ++) {
            long long mixedX = sourceX * seedX;
            long long mixedZ = sourceZ * seedZ;
            m_random.setSeed(mixedX ^ mixedZ ^ level->getSeed());
            addFeature(level, sourceX, sourceZ, chunkX, chunkZ, primer);
        }
    }
}

void LargeFeature::addFeature(Level*, int, int, int, int, ChunkPrimer*) {}
