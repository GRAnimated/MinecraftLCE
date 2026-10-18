#include "net/minecraft/world/level/biome/PlainsBiome.h"

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/eINSTANCEOF.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/biome/BiomeDecorator.h"
#include "net/minecraft/world/level/levelgen/feature/BigTreeFeature.h"
#include "net/minecraft/world/level/levelgen/feature/DoublePlantFeature.h"
#include "net/minecraft/world/level/levelgen/feature/TreeFeature.h"
#include "net/minecraft/world/level/levelgen/synth/PerlinSimplexNoise.h"

PlainsBiome::PlainsBiome(EBiomeIDs id, bool sunflowers, BiomeProperties* properties)
    : Biome(id, properties), m_sunflowers(sunflowers) {
    m_passiveMobs.push_back(new MobSpawnerData(eHorse, 5, 2, 6));
    m_passiveMobs.push_back(new MobSpawnerData(eDonkey, 1, 1, 3));
    m_biomeDecorator->m_treeCount = 0;
    m_biomeDecorator->m_extraTreeChance = 0.05f;
    m_biomeDecorator->m_flowerCount = 4;
    m_biomeDecorator->m_grassCount = 10;
}

int PlainsBiome::getBaseClass() {
    return _PLAINS;
}

Feature* PlainsBiome::getTreeFeature(Random& random) {
    if (random.nextInt(3) == 0)
        return new BigTreeFeature(false);
    return new TreeFeature(false);
}

FlowerBlock::Flower* PlainsBiome::getRandomFlower(Random& random, const BlockPos* pos) {
    double noise = BIOME_INFO_NOISE->getValue(pos->getX() / 200.0, pos->getZ() / 200.0);
    if (noise < -0.8) {
        switch (random.nextInt(4)) {
        case 0:
            return FlowerBlock::Flower::ORANGE_TULIP;
        case 1:
            return FlowerBlock::Flower::RED_TULIP;
        case 2:
            return FlowerBlock::Flower::PINK_TULIP;
        default:
            return FlowerBlock::Flower::WHITE_TULIP;
        }
    }
    if (random.nextInt(3) > 0) {
        int type = random.nextInt(3);
        if (type == 0)
            return FlowerBlock::Flower::RED_FLOWER;
        if (type == 1)
            return FlowerBlock::Flower::HOUSTONIA;
        return FlowerBlock::Flower::OXEYE_DAISY;
    }
    return FlowerBlock::Flower::YELLOW_FLOWER;
}

void PlainsBiome::decorate(Level* level, Random& random, const BlockPos& pos) {
    double noise = BIOME_INFO_NOISE->getValue((pos.getX() + 8) / 200.0, (pos.getZ() + 8) / 200.0);
    if (noise < -0.8) {
        m_biomeDecorator->m_flowerCount = 15;
        m_biomeDecorator->m_grassCount = 5;
    } else {
        m_biomeDecorator->m_flowerCount = 4;
        m_biomeDecorator->m_grassCount = 10;
        DOUBLE_PLANT_FEATURE->setNextPlantType(DoublePlantBlock::Variant::GRASS);
        for (int i = 0; i < 7; ++i) {
            int x = random.nextInt(16) + 8;
            int z = random.nextInt(16) + 8;
            int height = level->getHeightmapPos(pos.offset(x, 0, z)).getY();
            int y = random.nextInt(height + 32);
            DOUBLE_PLANT_FEATURE->place(level, random, pos.offset(x, y, z));
        }
    }
    if (m_sunflowers) {
        DOUBLE_PLANT_FEATURE->setNextPlantType(DoublePlantBlock::Variant::SUNFLOWER);
        for (int i = 0; i < 10; ++i) {
            int x = random.nextInt(16) + 8;
            int z = random.nextInt(16) + 8;
            int height = level->getHeightmapPos(pos.offset(x, 0, z)).getY();
            int y = random.nextInt(height + 32);
            DOUBLE_PLANT_FEATURE->place(level, random, pos.offset(x, y, z));
        }
    }
    Biome::decorate(level, random, pos);
}
