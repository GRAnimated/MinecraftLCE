#include "net/minecraft/world/level/biome/ExtremeHillsBiome.h"

#include "NX/Platform.h"
#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/biome/BiomeDecorator.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/MonsterEggBlock.h"
#include "net/minecraft/world/level/levelgen/feature/OreFeature.h"
#include "net/minecraft/world/level/levelgen/feature/SpruceFeature.h"

ExtremeHillsBiome::ExtremeHillsBiome(EBiomeIDs id, EType type, BiomeProperties* properties)
    : Biome(id, properties) {
    if (type == EDGE)
        m_biomeDecorator->m_treeCount = 3;
    m_passiveMobs.push_back(new MobSpawnerData(eLlama, 5, 4, 6));
    m_type = type;
    m_oreFeature = new OreFeature(Blocks::MONSTER_EGG->defaultBlockState()->setValue(
                                      MonsterEggBlock::VARIANT, MonsterEggBlock::Variant::STONE),
                                  9);
}

ExtremeHillsBiome::~ExtremeHillsBiome() {
    delete m_oreFeature;
}

int ExtremeHillsBiome::getBaseClass() {
    return _EXTREME_HILLS;
}

Feature* ExtremeHillsBiome::getTreeFeature(Random& random) {
    if (random.nextInt(3) > 0)
        return new SpruceFeature(false);
    return Biome::getTreeFeature(random);
}

void ExtremeHillsBiome::decorate(Level* level, Random& random, const BlockPos& pos) {
    Biome::decorate(level, random, pos);
    int count = random.nextInt(6) + 3;
    for (int i = 0; i < count; ++i) {
        int x = random.nextInt(16);
        int y = random.nextInt(28) + 4;
        int z = random.nextInt(16);
        BlockPos candidate = pos.offset(x, y, z);
        if (level->getBlockState(candidate)->getBlock() == Blocks::STONE)
            level->setBlock(candidate, Blocks::EMERALD_ORE->defaultBlockState(), 2, false);
    }
    for (int i = 0; i < 7; ++i) {
        int x = random.nextInt(16);
        int y = random.nextInt(64);
        int z = random.nextInt(16);
        m_oreFeature->place(level, random, pos.offset(x, y, z));
    }
}

void ExtremeHillsBiome::buildSurfaceAt(Level* level, Random& random, ChunkPrimer* primer, int x, int z,
                                       double noise) {
    PIXBeginNamedEvent(0.0f, "ExtremeHillsBiome::buildSurfaceAtDefault");
    m_grass = LegacyBlockData(2, 0);
    m_dirt = LegacyBlockData(3, 0);
    if ((noise < -1.0 || noise > 2.0) && m_type == M) {
        m_grass = LegacyBlockData(13, 0);
        m_dirt = LegacyBlockData(13, 0);
    } else if (noise > 1.0 && m_type != EDGE) {
        m_grass = LegacyBlockData(1, 0);
        m_dirt = LegacyBlockData(1, 0);
    }
    buildSurfaceAtDefault(level, random, primer, x, z, noise);
    PIXEndNamedEvent();
}
