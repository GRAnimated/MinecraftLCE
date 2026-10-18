#include "net/minecraft/world/level/biome/SwampBiome.h"

#include "NX/Platform.h"
#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/client/color/ColourTable.h"
#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/eINSTANCEOF.h"
#include "net/minecraft/world/level/biome/BiomeDecorator.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include "net/minecraft/world/level/levelgen/ChunkPrimer.h"
#include "net/minecraft/world/level/levelgen/feature/FossilFeature.h"
#include "net/minecraft/world/level/levelgen/feature/SwampTreeFeature.h"
#include "net/minecraft/world/level/levelgen/synth/PerlinSimplexNoise.h"
#include "net/minecraft/world/level/material/Material.h"

SwampBiome::SwampBiome(EBiomeIDs id, BiomeProperties* properties) : Biome(id, properties) {
    m_biomeDecorator->m_treeCount = 2;
    m_biomeDecorator->m_flowerCount = 1;
    m_biomeDecorator->m_deadBushCount = 1;
    m_biomeDecorator->m_mushroomCount = 8;
    m_biomeDecorator->m_reedCount = 10;
    m_biomeDecorator->m_clayCount = 1;
    m_biomeDecorator->m_waterlilyCount = 4;
    m_biomeDecorator->m_sandCount = 0;
    m_biomeDecorator->m_gravelPatchCount = 0;
    m_biomeDecorator->m_grassCount = 5;
    m_neutralMobs.push_back(new MobSpawnerData(eSlime, 1, 1, 1));
}

int SwampBiome::getBaseClass() {
    return _SWAMP;
}

Feature* SwampBiome::getTreeFeature(Random&) {
    return new SwampTreeFeature();
}

FlowerBlock::Flower* SwampBiome::getRandomFlower(Random&, const BlockPos*) {
    return FlowerBlock::Flower::BLUE_ORCHID;
}

unsigned int SwampBiome::getGrassColor(const BlockPos* pos) {
    double noise = BIOME_INFO_NOISE->getValue(pos->getX() * 0.0225, pos->getZ() * 0.0225);
    return Minecraft::GetInstance()->getColourTable()->getColour(noise < -0.1 ? Grass_Swamp1 : Grass_Swamp2);
}

unsigned int SwampBiome::getFoliageColor(const BlockPos*) {
    return Minecraft::GetInstance()->getColourTable()->getColour(Foliage_Swampland);
}

void SwampBiome::decorate(Level* level, Random& random, const BlockPos& pos) {
    Biome::decorate(level, random, pos);
    if (random.nextInt(64) == 0) {
        FossilFeature fossil{};
        fossil.place(level, random, pos);
    }
}

void SwampBiome::buildSurfaceAt(Level* level, Random& random, ChunkPrimer* primer, int x, int z,
                                double noise) {
    PIXBeginNamedEvent(0.0f, "SwampBiome::buildSurfaceAtDefault");
    double swampNoise = BIOME_INFO_NOISE->getValue(x * 0.25, z * 0.25);
    if (swampNoise > 0.0) {
        int localX = x & 15;
        int localZ = z & 15;
        unsigned int y = 128;
        do {
            unsigned int currentY = y - 1;
            Block* block = primer->getState(localZ, currentY, localX)->getBlock();
            if (block->getMaterial() != Material::AIR) {
                if (y == 63 && block != Blocks::WATER) {
                    int packedPos = (localZ << 11) | (localX << 7) | currentY;
                    primer->setBlockAndData(packedPos, WATER.m_id, WATER.m_data);
                    if (swampNoise < 0.12)
                        primer->setBlockAndData(packedPos + 1, WATERLILY.m_id, WATERLILY.m_data);
                }
                break;
            }
            y = currentY;
        } while (static_cast<int>(y) > 0);
    }
    buildSurfaceAtDefault(level, random, primer, x, z, noise);
    PIXEndNamedEvent();
}
