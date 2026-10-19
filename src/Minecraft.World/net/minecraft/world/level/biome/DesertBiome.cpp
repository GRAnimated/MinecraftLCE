#include "net/minecraft/world/level/biome/DesertBiome.h"

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/biome/BiomeDecorator.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/levelgen/feature/DesertWellFeature.h"
#include "net/minecraft/world/level/levelgen/feature/FossilFeature.h"

// name guessed
DesertBiome::DesertBiome(EBiomeIDs id, BiomeProperties* properties) : Biome(id, properties) {
    m_passiveMobs.clear();
    m_passiveMobs.push_back(new MobSpawnerData(eRabbit, 4, 2, 3));
    m_chickens.clear();
    m_fieldD8.clear();
    m_grass
        = LegacyBlockData(12, Blocks::SAND->convertBlockStateToLegacyData(Blocks::SAND->defaultBlockState()));
    m_dirt
        = LegacyBlockData(12, Blocks::SAND->convertBlockStateToLegacyData(Blocks::SAND->defaultBlockState()));
    m_biomeDecorator->m_treeCount = -999;
    m_biomeDecorator->m_deadBushCount = 2;
    m_biomeDecorator->m_reedCount = 50;
    m_biomeDecorator->m_cactusCount = 10;
    // The original advances after erasure, skipping the entry shifted into this slot.
    for (auto it = m_hostileMobs.begin(); it != m_hostileMobs.end(); ++it) {
        MobSpawnerData* mob = *it;
        if (mob->m_instanceType == eZombie || mob->m_instanceType == eZombieVillager) {
            it = m_hostileMobs.erase(it);
            delete mob;
        }
    }
    m_hostileMobs.push_back(new MobSpawnerData(eZombie, 19, 4, 4));
    m_hostileMobs.push_back(new MobSpawnerData(eZombieVillager, 1, 1, 1));
    m_hostileMobs.push_back(new MobSpawnerData(eHusk, 80, 4, 4));
}

// name guessed
int DesertBiome::getBaseClass() {
    return _DESERT;
}

// name guessed
// NON_MATCHING | score: 100 (lower is better)
void DesertBiome::decorate(Level* level, Random& random, const BlockPos& pos) {
    Biome::decorate(level, random, pos);
    if (random.nextInt(1000) == 0) {
        int x = random.nextInt(16) + 8;
        int z = random.nextInt(16) + 8;
        BlockPos candidate = level->getHeightmapPos(pos.offset(x, 0, z)).above();
        DesertWellFeature well;
        well.place(level, random, candidate);
    }
    if (random.nextInt(64) == 0) {
        FossilFeature fossil{};
        fossil.place(level, random, pos);
    }
}
