#include "net/minecraft/world/level/levelgen/FlatLevelSource.h"

#include "NX/Platform.h"
#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/entity/MobCategory.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/biome/BiomeSource.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include "net/minecraft/world/level/chunk/ChunkPos.h"
#include "net/minecraft/world/level/chunk/LevelChunk.h"
#include "net/minecraft/world/level/levelgen/ChunkPrimer.h"
#include "net/minecraft/world/level/levelgen/FlatGeneratorInfo.h"
#include "net/minecraft/world/level/levelgen/feature/CanyonFeature.h"
#include "net/minecraft/world/level/levelgen/feature/LakeFeature.h"
#include "net/minecraft/world/level/levelgen/feature/LargeCaveFeature.h"
#include "net/minecraft/world/level/levelgen/feature/MonsterRoomFeature.h"
#include "net/minecraft/world/level/levelgen/feature/OceanMonumentFeature.h"
#include "net/minecraft/world/level/levelgen/feature/VillageFeature.h"
#include "net/minecraft/world/level/levelgen/feature/WoodlandMansionFeature.h"
#include "net/minecraft/world/level/storage/LevelData.h"
#include <algorithm>
#include <cstring>

// NON_MATCHING | score: 6910 (lower is better)
FlatLevelSource::FlatLevelSource(Level* level, long long seed, bool structures, SuperflatConfig* config) {
    m_monument = nullptr;
    m_size = level->getLevelData()->getXZSize();
    m_level = level;
    m_random = Random(seed);
    m_decorationRandom = Random(seed);
    FlatGeneratorInfo settings(config);
    m_caves = nullptr;
    m_canyons = nullptr;
    if (structures) {
        m_caves = settings.getCaves();
        m_canyons = settings.getCanyons();
        if (settings.hasVillage())
            m_structures[VILLAGE_NAME] = settings.getVillage(m_size);
        if (settings.hasBiomeSpecific())
            m_structures[TEMPLE_NAME] = settings.getBiomeSpecific();
        if (settings.hasMineshaft())
            m_structures[MINESHAFT_NAME] = settings.getMineshaft();
        if (settings.hasStronghold())
            m_structures[STRONGHOLD_NAME] = settings.getStronghold();
        if (settings.hasOceanMonument()) {
            m_monument = settings.getOceanMonument();
            m_structures[MONUMENT_NAME] = m_monument;
        }
        if (settings.hasWoodlandMansion())
            m_structures[MANSION_NAME] = new WoodlandMansionFeature(this, config);
    }
    m_decorations = settings.hasDecorations();
    m_dungeons = settings.hasDungeons();
    m_lakes = settings.getLakes();
    m_lavaLakes = settings.getLavaLakes();
    memset(m_layers, 0, sizeof(m_layers));
    settings.getLayers(m_layers);
    std::vector<FlatLayerInfo> layers;
    settings.getLayers(layers);
    int seaLevel = 0;
    int air = 0;
    for (FlatLayerInfo layer : layers) {
        Block* block;
        int y = layer.getHeight() - 1;
        do {
            int end = layer.getHeight() + layer.getStart();
            block = layer.getBlockState()->getBlock();
            ++y;
            if (y >= end)
                break;
        } while (true);
        air += layer.getStart();
        if (block != Blocks::AIR) {
            seaLevel += air;
            air = 0;
        }
    }
    level->setSeaLevel(seaLevel);
    m_blockIds = arrayWithLength<unsigned char>(0x10000, true);
    m_blockData = arrayWithLength<unsigned char>(0x8000, true);
    ChunkPrimer primer(false, m_blockIds, m_blockData);
    for (int y = 0; y < 128; ++y) {
        if (m_layers[y]) {
            for (int x = 0; x < 16; ++x) {
                for (int z = 0; z < 16; ++z)
                    primer.setState(x, y, z, m_layers[y]);
            }
        }
    }
}

FlatLevelSource::~FlatLevelSource() {
    delete m_caves;
    delete m_canyons;
    for (auto& structure : m_structures)
        delete structure.second;
    delete m_lakes;
    delete m_lavaLakes;
    delete[] m_blockIds.m_data;
    delete[] m_blockData.m_data;
}

// name guessed
void FlatLevelSource::prepareHeights(int, int, ChunkPrimer* primer) {
    memcpy(primer->getBlockIds().m_data, m_blockIds.m_data, m_blockIds.m_length);
    memcpy(primer->getBlockData().m_data, m_blockData.m_data, m_blockData.m_length);
}

// name guessed
bool FlatLevelSource::isFlat() {
    return true;
}

LevelChunk* FlatLevelSource::createChunk(int x, int z) {
    arrayWithLength<unsigned char> ids(
        static_cast<unsigned char*>(XPhysicalAlloc(m_blockIds.m_length, -1, 0x1000, 4)), m_blockIds.m_length);
    XMemCpy(ids.m_data, m_blockIds.m_data, m_blockIds.m_length);
    arrayWithLength<unsigned char> data(
        static_cast<unsigned char*>(XPhysicalAlloc(m_blockData.m_length, -1, 0x1000, 4)),
        m_blockData.m_length);
    XMemCpy(data.m_data, m_blockData.m_data, m_blockData.m_length);
    ChunkPrimer primer(false, ids, data);
    if (m_caves)
        m_caves->apply(m_level, x, z, &primer);
    if (m_canyons)
        m_canyons->apply(m_level, x, z, &primer);
    for (auto& structure : m_structures)
        structure.second->apply(m_level, x, z, &primer);
    LevelChunk* chunk = new LevelChunk(m_level, &primer, x, z);
    XPhysicalFree(ids.m_data);
    XPhysicalFree(data.m_data);
    arrayWithLength<Biome*> biomes;
    m_level->getBiomeSource()->getBiomeBlock(biomes, x << 4, z << 4, 16, 16, true);
    arrayWithLength<unsigned char> chunkBiomes = chunk->getBiomes();
    for (unsigned int i = 0; i < chunkBiomes.m_length; ++i)
        chunkBiomes[i] = biomes.get(i)->m_biomeId;
    delete[] biomes.m_data;
    chunk->recalcHeightmap();
    return chunk;
}

// NON_MATCHING | score: 1725 (lower is better)
void FlatLevelSource::postProcess(int x, int z) {
    BlockPos origin(x * 16, 0, z * 16);
    Biome* biome = m_level->getBiome(BlockPos(x * 16 + 16, 0, z * 16 + 16));
    m_decorationRandom.setSeed(m_level->getSeed());
    long long seedX = m_decorationRandom.nextLong() / 2 * 2 + 1;
    long long seedZ = m_decorationRandom.nextLong() / 2 * 2 + 1;
    m_decorationRandom.setSeed((x * seedX + z * seedZ) ^ m_level->getSeed());
    ChunkPos chunkPos(x, z);
    bool village = false;
    for (auto& entry : m_structures) {
        bool placed = entry.second->postProcess(m_level, m_decorationRandom, &chunkPos);
        if (dynamic_cast<VillageFeature*>(entry.second)) {
            bool allowed = std::find(VillageFeature::ALLOWED_BIOMES.begin(),
                                     VillageFeature::ALLOWED_BIOMES.end(), biome)
                           != VillageFeature::ALLOWED_BIOMES.end();
            village |= placed && allowed;
        }
    }
    if (!village && m_lakes && m_decorationRandom.nextInt(4) == 0) {
        int px = m_decorationRandom.nextInt(16) + 8;
        int py = m_decorationRandom.nextInt(128);
        int pz = m_decorationRandom.nextInt(16) + 8;
        m_lakes->place(m_level, m_decorationRandom, origin.offset(px, py, pz));
    }
    if (!village && m_lavaLakes && m_random.nextInt(8) == 0) {
        int px = m_decorationRandom.nextInt(16) + 8;
        int py = m_decorationRandom.nextInt(m_decorationRandom.nextInt(120) + 8);
        int pz = m_decorationRandom.nextInt(16) + 8;
        BlockPos pos = origin.offset(px, py, pz);
        if (pos.getY() < m_level->getSeaLevel() || m_decorationRandom.nextInt(10) == 0)
            m_lavaLakes->place(m_level, m_decorationRandom, pos);
    }
    if (m_dungeons) {
        for (int i = 0; i < 8; ++i) {
            MonsterRoomFeature dungeon;
            int px = m_decorationRandom.nextInt(16) + 8;
            int py = m_decorationRandom.nextInt(128);
            int pz = m_decorationRandom.nextInt(16) + 8;
            dungeon.place(m_level, m_decorationRandom, origin.offset(px, py, pz));
        }
    }
    if (m_decorations)
        biome->decorate(m_level, m_decorationRandom, origin);
    CConsoleMinecraftApp::sInstance.processSchematics(m_level->getChunk(x, z));
}

bool FlatLevelSource::postProcessLoadedChunk(LevelChunk*, int, int) {
    return false;
}

std::vector<Biome::MobSpawnerData*>* FlatLevelSource::getMobsAt(MobCategory* category, const BlockPos& pos) {
    Biome* biome = m_level->getBiome(pos);
    if (m_monument && category == MobCategory::GUARDIAN && m_monument->isInsideBoundingFeature(m_level, pos))
        return m_monument->getEnemies();
    return biome->getMobs(category);
}

// NON_MATCHING | score: 590 (lower is better)
BlockPos* FlatLevelSource::findNearestMapFeature(Level* level, const std::wstring& name, const BlockPos& pos,
                                                 bool unexplored) {
    if (STRONGHOLD_NAME.compare(name) == 0 && m_structures.find(name) != m_structures.end())
        return m_structures.find(name)->second->getNearestGeneratedFeature(level, pos, unexplored);
    if (STRONGHOLD_NAME == name && m_structures.find(STRONGHOLD_NAME) != m_structures.end())
        return m_structures.find(STRONGHOLD_NAME)->second->getNearestGeneratedFeature(level, pos, unexplored);
    if (MANSION_NAME == name && m_structures.find(MANSION_NAME) != m_structures.end())
        return m_structures.find(MANSION_NAME)->second->getNearestGeneratedFeature(level, pos, unexplored);
    if (MONUMENT_NAME == name && m_structures.find(MONUMENT_NAME) != m_structures.end())
        return m_structures.find(MONUMENT_NAME)->second->getNearestGeneratedFeature(level, pos, unexplored);
    if (VILLAGE_NAME == name && m_structures.find(VILLAGE_NAME) != m_structures.end())
        return m_structures.find(VILLAGE_NAME)->second->getNearestGeneratedFeature(level, pos, unexplored);
    if (MINESHAFT_NAME == name && m_structures.find(MINESHAFT_NAME) != m_structures.end())
        return m_structures.find(MINESHAFT_NAME)->second->getNearestGeneratedFeature(level, pos, unexplored);
    if (TEMPLE_NAME == name && m_structures.find(TEMPLE_NAME) != m_structures.end())
        return m_structures.find(TEMPLE_NAME)->second->getNearestGeneratedFeature(level, pos, unexplored);
    return nullptr;
}

bool FlatLevelSource::isPosInFeature(Level*, const std::wstring& name, const BlockPos& pos) {
    auto found = m_structures.find(name);
    return found != m_structures.end() && found->second->isInsideFeature(pos);
}

void FlatLevelSource::recreateLogicStructuresForChunk(LevelChunk*, int x, int z) {
    for (auto& entry : m_structures)
        entry.second->apply(m_level, x, z, nullptr);
}
