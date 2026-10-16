#include "net/minecraft/world/level/biome/ForestBiome.h"

#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/client/color/ColourTable.h"
#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/util/Mth.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/eINSTANCEOF.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/biome/BiomeDecorator.h"
#include "net/minecraft/world/level/levelgen/feature/BigTreeFeature.h"
#include "net/minecraft/world/level/levelgen/feature/BirchFeature.h"
#include "net/minecraft/world/level/levelgen/feature/DoublePlantFeature.h"
#include "net/minecraft/world/level/levelgen/feature/HugeMushroomFeature.h"
#include "net/minecraft/world/level/levelgen/feature/RoofTreeFeature.h"
#include "net/minecraft/world/level/levelgen/feature/TreeFeature.h"
#include "net/minecraft/world/level/levelgen/synth/PerlinSimplexNoise.h"

ForestBiome::ForestBiome(EBiomeIDs id, EType type, BiomeProperties* properties)
    : Biome(id, properties), m_type(type) {
    m_biomeDecorator->m_treeCount = 10;
    m_biomeDecorator->m_grassCount = 2;
    if (type == DEFAULT) {
        m_fieldD8.push_back(new MobSpawnerData(eWolf, 5, 4, 4));
    }
    if (type == ROOFED) {
        m_biomeDecorator->m_treeCount = -999;
    }
    if (type == FLOWER) {
        m_biomeDecorator->m_treeCount = 6;
        m_biomeDecorator->m_flowerCount = 100;
        m_biomeDecorator->m_grassCount = 1;
        m_passiveMobs.push_back(new MobSpawnerData(eRabbit, 4, 2, 3));
    }
}

int ForestBiome::getBaseClass() {
    return _FOREST;
}

Feature* ForestBiome::getTreeFeature(Random& random) {
    if (m_type == ROOFED && random.nextInt(3) > 0)
        return new RoofTreeFeature(false);
    if (m_type == BIRCH || random.nextInt(5) == 0)
        return new BirchFeature(false, false);
    if (random.nextInt(10) == 0)
        return new BigTreeFeature(false);
    return new TreeFeature(false);
}

FlowerBlock::Flower* ForestBiome::getRandomFlower(Random& random, const BlockPos* pos) {
    if (m_type == FLOWER) {
        double noise = BIOME_INFO_NOISE->getValue(pos->getX() / 48.0, pos->getZ() / 48.0);
        int index = static_cast<int>(Mth::clamp((noise + 1.0) * 0.5, 0.0, 0.9999) * 10.0);
        FlowerBlock::Flower* flower = FlowerBlock::Flower::FLOWERS[index];
        return flower == FlowerBlock::Flower::BLUE_ORCHID ? FlowerBlock::Flower::RED_FLOWER : flower;
    }
    return Biome::getRandomFlower(random, pos);
}

unsigned int ForestBiome::getGrassColor(const BlockPos* pos) {
    unsigned int color = Biome::getGrassColor(pos);
    if (m_type == ROOFED) {
        color &= 0xfefefe;
        unsigned int modifier
            = Minecraft::GetInstance()->getColourTable()->getColour(Grass_Roofed_Forest_Modifier);
        return ((modifier & 0xfefefe) + color) >> 1;
    }
    return color;
}

void ForestBiome::decorate(Level* level, Random& random, const BlockPos& pos) {
    if (m_type == ROOFED)
        addMushrooms(level, random, pos);
    int count = random.nextInt(5) - 3;
    if (m_type == FLOWER)
        count += 2;
    addDoublePlants(level, random, pos, count);
    Biome::decorate(level, random, pos);
}

void ForestBiome::addMushrooms(Level* level, Random& random, const BlockPos& pos) {
    for (int x = 0; x < 4; ++x) {
        for (int z = 0; z < 4; ++z) {
            int dx = x * 4 + 1 + 8 + random.nextInt(3);
            int dz = z * 4 + 1 + 8 + random.nextInt(3);
            BlockPos candidate = level->getHeightmapPos(pos.offset(dx, 0, dz));
            if (random.nextInt(20) == 0) {
                HugeMushroomFeature* mushroom = new HugeMushroomFeature();
                mushroom->place(level, random, candidate);
                delete mushroom;
            } else {
                AbstractTreeFeature* tree = static_cast<AbstractTreeFeature*>(getTreeFeature(random));
                tree->init();
                if (tree->place(level, random, candidate))
                    tree->postPlaceTree(level, random, candidate);
                delete tree;
            }
        }
    }
}

void ForestBiome::addDoublePlants(Level* level, Random& random, const BlockPos& pos, int count) {
    for (int i = 0; i < count; ++i) {
        int type = random.nextInt(3);
        if (type == 0)
            DOUBLE_PLANT_FEATURE->setNextPlantType(DoublePlantBlock::Variant::SYRINGA);
        else if (type == 1)
            DOUBLE_PLANT_FEATURE->setNextPlantType(DoublePlantBlock::Variant::ROSE);
        else if (type == 2)
            DOUBLE_PLANT_FEATURE->setNextPlantType(DoublePlantBlock::Variant::PAEONIA);
        for (int attempt = 0; attempt < 5; ++attempt) {
            int x = random.nextInt(16) + 8;
            int z = random.nextInt(16) + 8;
            int height = level->getHeightmapPos(pos.offset(x, 0, z)).getY();
            int y = random.nextInt(height + 32);
            BlockPos candidate(pos.getX() + x, y, pos.getZ() + z);
            if (DOUBLE_PLANT_FEATURE->place(level, random, candidate))
                break;
        }
    }
}
