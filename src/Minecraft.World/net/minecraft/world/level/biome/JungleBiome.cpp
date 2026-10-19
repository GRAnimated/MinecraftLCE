#include "net/minecraft/world/level/biome/JungleBiome.h"

#include "NX/Platform.h"
#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/biome/BiomeDecorator.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/OldLeafBlock.h"
#include "net/minecraft/world/level/block/OldLogBlock.h"
#include "net/minecraft/world/level/levelgen/feature/BigTreeFeature.h"
#include "net/minecraft/world/level/levelgen/feature/GroundBushFeature.h"
#include "net/minecraft/world/level/levelgen/feature/MegaJungleTreeFeature.h"
#include "net/minecraft/world/level/levelgen/feature/MelonFeature.h"
#include "net/minecraft/world/level/levelgen/feature/TallgrassFeature.h"
#include "net/minecraft/world/level/levelgen/feature/VinesFeature.h"

const BlockState* JungleBiome::TRUNK;  // name guessed
const BlockState* JungleBiome::LEAVES;
const BlockState* JungleBiome::BUSH_LEAVES;

void JungleBiome::staticCtor() {
    TRUNK = Blocks::LOG->defaultBlockState()->setValue(OldLogBlock::VARIANT, PlanksBlock::Variant::JUNGLE);
    LEAVES = Blocks::LEAVES->defaultBlockState()
                 ->setValue(OldLeafBlock::VARIANT, PlanksBlock::Variant::JUNGLE)
                 ->setValue(LeafBlock::CHECK_DECAY, false);
    BUSH_LEAVES = Blocks::LEAVES->defaultBlockState()
                      ->setValue(OldLeafBlock::VARIANT, PlanksBlock::Variant::OAK)
                      ->setValue(LeafBlock::CHECK_DECAY, false);
}

// name guessed
JungleBiome::JungleBiome(EBiomeIDs id, bool edge, BiomeProperties* properties)
    : Biome(id, properties), m_edge(edge) {
    if (edge)
        m_biomeDecorator->m_treeCount = 2;
    else
        m_biomeDecorator->m_treeCount = 50;
    m_biomeDecorator->m_grassCount = 25;
    m_biomeDecorator->m_flowerCount = 4;
    if (!edge)
        m_hostileMobs.push_back(new MobSpawnerData(eOcelot, 2, 1, 1));
    m_passiveMobs.push_back(new MobSpawnerData(eParrot, 40, 1, 2));
    m_passiveMobs.push_back(new MobSpawnerData(eChicken, 10, 4, 4));
}

// name guessed
int JungleBiome::getBaseClass() {
    return _JUNGLE;
}

// name guessed
Feature* JungleBiome::getTreeFeature(Random& random) {
    if (random.nextInt(10) == 0)
        return new BigTreeFeature(false);
    if (random.nextInt(2) == 0)
        return new GroundBushFeature(TRUNK, BUSH_LEAVES);
    if (!m_edge && random.nextInt(3) == 0)
        return new MegaJungleTreeFeature(false, 10, 20, TRUNK, LEAVES);
    return new TreeFeature(false, 4 + random.nextInt(7), TRUNK, LEAVES, true);
}

// name guessed
Feature* JungleBiome::getGrassFeature(Random& random) {
    if (random.nextInt(4) == 0)
        return new TallgrassFeature(TallGrassBlock::Variant::FERN);
    return new TallgrassFeature(TallGrassBlock::Variant::GRASS);
}

// name guessed
void JungleBiome::decorate(Level* level, Random& random, const BlockPos& pos) {
    Biome::decorate(level, random, pos);
    int x = random.nextInt(16) + 8;
    int z = random.nextInt(16) + 8;
    int height = level->getHeightmapPos(pos.offset(x, 0, z)).getY();
    int y = height < 1 ? 0 : random.nextInt(height * 2);
    {
        MelonFeature melon;
        melon.place(level, random, pos.offset(x, y, z));
    }
    PIXBeginNamedEvent(0.0f, "Adding vines");
    VinesFeature vines;
    for (int i = 0; i < 50; ++i) {
        x = random.nextInt(16) + 8;
        z = random.nextInt(16) + 8;
        vines.place(level, random, pos.offset(x, 64, z));
    }
    PIXEndNamedEvent();
}
