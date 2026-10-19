#include "net/minecraft/world/level/biome/TaigaBiome.h"

#include "NX/Platform.h"
#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/eINSTANCEOF.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/biome/BiomeDecorator.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/DirtBlock.h"
#include "net/minecraft/world/level/levelgen/feature/BlockBlobFeature.h"
#include "net/minecraft/world/level/levelgen/feature/DoublePlantFeature.h"
#include "net/minecraft/world/level/levelgen/feature/MegaPineTreeFeature.h"
#include "net/minecraft/world/level/levelgen/feature/PineFeature.h"
#include "net/minecraft/world/level/levelgen/feature/SpruceFeature.h"
#include "net/minecraft/world/level/levelgen/feature/TallgrassFeature.h"

// name guessed
TaigaBiome::TaigaBiome(EBiomeIDs id, EType type, BiomeProperties* properties)
    : Biome(id, properties), m_type(type) {
    m_fieldD8.push_back(new MobSpawnerData(eWolf, 8, 4, 4));
    m_passiveMobs.push_back(new MobSpawnerData(eRabbit, 4, 2, 3));
    m_biomeDecorator->m_treeCount = 10;
    if (type == MEGA || type == MEGA_SPRUCE) {
        m_biomeDecorator->m_grassCount = 7;
        m_biomeDecorator->m_deadBushCount = 1;
        m_biomeDecorator->m_mushroomCount = 3;
    } else {
        m_biomeDecorator->m_grassCount = 1;
        m_biomeDecorator->m_mushroomCount = 1;
    }
}

// name guessed
int TaigaBiome::getBaseClass() {
    return _TAIGA;
}

// name guessed
Feature* TaigaBiome::getTreeFeature(Random& random) {
    if ((m_type == MEGA || m_type == MEGA_SPRUCE) && random.nextInt(3) == 0) {
        if (m_type == MEGA_SPRUCE || random.nextInt(13) == 0)
            return new MegaPineTreeFeature(false, true);
        return new MegaPineTreeFeature(false, false);
    }
    if (random.nextInt(3) == 0)
        return new PineFeature();
    return new SpruceFeature(false);
}

// name guessed
Feature* TaigaBiome::getGrassFeature(Random& random) {
    if (random.nextInt(5) > 0)
        return new TallgrassFeature(TallGrassBlock::Variant::FERN);
    return new TallgrassFeature(TallGrassBlock::Variant::GRASS);
}

// name guessed
void TaigaBiome::decorate(Level* level, Random& random, const BlockPos& pos) {
    if (m_type == MEGA || m_type == MEGA_SPRUCE) {
        int count = random.nextInt(3);
        for (int i = 0; i < count; ++i) {
            int x = random.nextInt(16) + 8;
            int z = random.nextInt(16) + 8;
            BlockPos candidate = level->getHeightmapPos(pos.offset(x, 0, z));
            BlockBlobFeature blob(Blocks::MOSSY_COBBLESTONE, 0);
            blob.place(level, random, candidate);
        }
    }

    DOUBLE_PLANT_FEATURE->setNextPlantType(DoublePlantBlock::Variant::FERN);
    for (int i = 0; i < 7; ++i) {
        int x = random.nextInt(16) + 8;
        int z = random.nextInt(16) + 8;
        int height = level->getHeightmapPos(pos.offset(x, 0, z)).getY();
        int y = random.nextInt(height + 32);
        DOUBLE_PLANT_FEATURE->place(level, random, pos.offset(x, y, z));
    }
    Biome::decorate(level, random, pos);
}

// name guessed
void TaigaBiome::buildSurfaceAt(Level* level, Random& random, ChunkPrimer* primer, int x, int z,
                                double noise) {
    PIXBeginNamedEvent(0.0f, "TaigaBiome::buildSurfaceAtDefault");
    if (m_type == MEGA || m_type == MEGA_SPRUCE) {
        m_grass = LegacyBlockData(2, 0);
        m_dirt = LegacyBlockData(3, 0);
        if (noise > 1.75) {
            m_grass = LegacyBlockData(
                3, Blocks::DIRT->convertBlockStateToLegacyData(Blocks::DIRT->defaultBlockState()->setValue(
                       DirtBlock::VARIANT, DirtBlock::Variant::COARSE)));
        } else if (noise > -0.95) {
            m_grass = LegacyBlockData(
                3, Blocks::DIRT->convertBlockStateToLegacyData(Blocks::DIRT->defaultBlockState()->setValue(
                       DirtBlock::VARIANT, DirtBlock::Variant::PODZOL)));
        }
    }
    buildSurfaceAtDefault(level, random, primer, x, z, noise);
    PIXEndNamedEvent();
}
