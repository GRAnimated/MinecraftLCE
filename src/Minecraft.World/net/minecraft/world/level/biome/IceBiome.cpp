#include "net/minecraft/world/level/biome/IceBiome.h"

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/levelgen/feature/IcePatchFeature.h"
#include "net/minecraft/world/level/levelgen/feature/IceSpikeFeature.h"
#include "net/minecraft/world/level/levelgen/feature/SpruceFeature.h"

IceBiome::IceBiome(EBiomeIDs id, bool spikes, BiomeProperties* properties) : Biome(id, properties) {
    m_spikeFeature = new IceSpikeFeature();
    m_patchFeature = new IcePatchFeature(4);
    m_spikes = spikes;
    if (spikes)
        m_grass = LegacyBlockData(
            80, Blocks::SNOW->convertBlockStateToLegacyData(Blocks::SNOW->defaultBlockState()));
    m_passiveMobs.clear();
    m_passiveMobs.push_back(new MobSpawnerData(eRabbit, 10, 2, 3));
    m_passiveMobs.push_back(new MobSpawnerData(ePolarBear, 1, 1, 2));
    for (auto it = m_hostileMobs.begin(); it != m_hostileMobs.end();) {
        if ((*it)->m_instanceType == eSkeleton)
            it = m_hostileMobs.erase(it);
        else
            ++it;
    }
    m_hostileMobs.push_back(new MobSpawnerData(eSkeleton, 20, 4, 4));
    m_hostileMobs.push_back(new MobSpawnerData(eStray, 80, 4, 4));
}

int IceBiome::getBaseClass() {
    return _ICE;
}
float IceBiome::getCreatureProbability() {
    return 0.07f;
}
Feature* IceBiome::getTreeFeature(Random&) {
    return new SpruceFeature(false);
}

void IceBiome::decorate(Level* level, Random& random, const BlockPos& pos) {
    if (m_spikes) {
        for (int i = 0; i < 3; ++i) {
            int x = random.nextInt(16) + 8;
            int z = random.nextInt(16) + 8;
            m_spikeFeature->place(level, random, level->getHeightmapPos(pos.offset(x, 0, z)));
        }
        for (int i = 0; i < 2; ++i) {
            int x = random.nextInt(16) + 8;
            int z = random.nextInt(16) + 8;
            m_patchFeature->place(level, random, level->getHeightmapPos(pos.offset(x, 0, z)));
        }
    }
    Biome::decorate(level, random, pos);
}
