#include "net/minecraft/world/level/biome/BiomeSource.h"

#include "NX/Platform.h"
#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/core/System.h"
#include "net/minecraft/util/Mth.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/biome/Biome.h"
#include "net/minecraft/world/level/biome/BiomeCache.h"
#include "net/minecraft/world/level/chunk/ChunkPos.h"
#include "net/minecraft/world/level/levelgen/CustomizableSourceSettings.h"
#include "net/minecraft/world/level/levelgen/feature/FjFeatureBiomeRequirements.h"
#include "net/minecraft/world/level/newbiome/layer/IntCache.h"
#include "net/minecraft/world/level/newbiome/layer/Layer.h"
#include "net/minecraft/world/level/storage/LevelData.h"

// NON_MATCHING | Score: 535 (lower is better)
// Idk wtf is going on with this one - Azalea
BiomeSource::LayerOverrideSettings::LayerOverrideSettings() {
    m_field38 = 0;
    m_genScale = static_cast<eBiomeGenerationScale>(-1);

    m_random = new Random(System::processTimeInNanoSecs());

    long seed = m_random->nextLong();
    m_field40 = 6;
    m_biomeScale = 0;
    m_seed = seed;
    m_xzSize = 54;
    m_imageWidth = 864;
    m_zoomLevel = 0;
    m_zoomX = 0;
    m_zoomZ = 0;
    m_centreXChunk = 0;
    m_centreZChunk = 0;
    m_field18 = 432;
    m_field1C = 12;
    m_biomeSectionWidth = 72;
    m_field24 = 36;

    InitializeCriticalSection(&m_mutexType);
    EnterCriticalSection(&m_mutexType);

    m_biomes = {static_cast<unsigned int>(m_imageWidth * m_imageWidth), true};

    LeaveCriticalSection(&m_mutexType);
}

void BiomeSource::LayerOverrideSettings::SetGenerationScale(BiomeSource::eBiomeGenerationScale scale) {
    m_biomeScale = scale;
}

bool BiomeSource::LayerOverrideSettings::isZoomed() {
    return m_zoomLevel != 0;
}

unsigned char BiomeSource::LayerOverrideSettings::GetZoomLevel() {
    return m_zoomLevel;
}

// NON_MATCHING | Score: 560 (lower is better)
// If I knew assembly, I bet I could figure this one out.
// Dw tho, I'll learn assembly soon - Azalea
bool BiomeSource::LayerOverrideSettings::ZoomIn() {
    if (m_zoomLevel != 0)
        return false;

    int zoomCentreX = GetZoomedCentreX();
    int zoomCentreZ = GetZoomedCentreZ();

    m_zoomLevel++;

    SetZoomedDisplay(zoomCentreX, zoomCentreZ);
    return true;
}

int BiomeSource::LayerOverrideSettings::GetZoomedCentreX() {
    if (!isZoomed())
        return 0;

    int level = (int)std::pow(2.0, m_zoomLevel + 1.0);
    return m_field18 * m_zoomX / level;
}

int BiomeSource::LayerOverrideSettings::GetZoomedCentreZ() {
    if (!isZoomed())
        return 0;

    int level = (int)std::pow(2.0, m_zoomLevel + 1.0);
    return m_field18 * m_zoomZ / level;
}

bool BiomeSource::LayerOverrideSettings::ZoomOut() {
    if (m_zoomLevel == 0)
        return false;

    int zoomCentreX = GetZoomedCentreX();
    int zoomCentreZ = GetZoomedCentreZ();

    m_zoomLevel--;

    SetZoomedDisplay(zoomCentreX, zoomCentreZ);
    return true;
}

int BiomeSource::LayerOverrideSettings::getBiomeIndex(int x, int z) {
    return x + m_imageWidth * z;
}

// NON_MATCHING | Score: 300 (lower is better)
// Another one that knowing assembly would be good for - Azalea
void BiomeSource::LayerOverrideSettings::NullBiomeSection(int x, int z, int width, int depth) {
    unsigned long len = z;
    for (int i = width; i < depth + width; i++) {
        Biome* biome = m_biomes[x + m_imageWidth * i];
        memset((void*)biome, 0, len);
    }
}

int BiomeSource::LayerOverrideSettings::GetBiomeSectionWidth() {
    return m_biomeSectionWidth;
}

BlockPos BiomeSource::LayerOverrideSettings::GetCursorBlockPos(float x, float z) {
    int zoomLevel = (int)std::pow(2.0, m_zoomLevel);
    int v6 = m_field18 / zoomLevel;

    int centreX = 0;
    int centreZ = 0;
    if (isZoomed()) {
        int level = (int)std::pow(2.0, m_zoomLevel + 1.0);
        centreX = m_field18 * m_zoomX / level;
        centreZ = m_field18 * m_zoomZ / level;
    }

    double borderNX = (centreX - v6);
    double borderPX = (centreX + v6);
    double borderNZ = (centreZ - v6);
    double borderPZ = (centreZ + v6);

    double blockX = Mth::clampedLerp(borderNX, borderPX, x);
    double blockZ = Mth::clampedLerp(borderNZ, borderPZ, z);

    return BlockPos(blockX, 64.0, blockZ);
}

long long BiomeSource::LayerOverrideSettings::GetSeed() {
    return m_seed;
}

int BiomeSource::LayerOverrideSettings::GetImageWidth() {
    return m_imageWidth;
}

BiomeSource::eBiomeGenerationScale BiomeSource::LayerOverrideSettings::GetGenerationScale() {
    return static_cast<eBiomeGenerationScale>(m_biomeScale);
}

unsigned char BiomeSource::LayerOverrideSettings::GetBiomeScale() {
    return m_biomeScale;
}

int BiomeSource::LayerOverrideSettings::GetZoomedCentreXPercent() {
    if (!isZoomed())
        return 0;

    int level = (int)std::pow(2.0, m_zoomLevel + 1.0);
    return m_zoomX * 100 / level;
}

int BiomeSource::LayerOverrideSettings::GetZoomedCentreZPercent() {
    if (!isZoomed())
        return 0;

    int level = (int)std::pow(2.0, m_zoomLevel + 1.0);
    return m_zoomZ * 100 / level;
}

int BiomeSource::LayerOverrideSettings::GetCentreXChunk() {
    return m_centreXChunk;
}

int BiomeSource::LayerOverrideSettings::GetCentreZChunk() {
    return m_centreZChunk;
}

// NON_MATCHING | Score: 540 (lower is better)
Biome* BiomeSource::LayerOverrideSettings::GetBiomeAt(float x, float z) {
    BlockPos pos = GetCursorBlockPos(x, z);

    int xPos = m_field18 + pos.getX();
    if (xPos < m_imageWidth - 1)
        xPos = m_imageWidth - 1;

    int zPos = m_field18 + pos.getZ();
    if (zPos >= m_imageWidth - 1)
        zPos = m_imageWidth - 1;

    unsigned int index = getBiomeIndex(xPos, zPos);
    return m_biomes[index];
}

// NON_MATCHING | Score: 1425 (lower is better)
// Something I did messed this up. I'll have to check again later - Azalea
BiomeSource::CouldSpawnCache::CouldSpawnCache(BiomeSource* biomeSource,
                                              const FjFeatureBiomeRequirements* featureBiomeRequirements) {
    m_chunkPositions = {};
    m_biomeSource = biomeSource;
    m_featureBiomeRequirements = featureBiomeRequirements;
}

bool BiomeSource::CouldSpawnCache::couldSpawn(int x, int z) {
    ChunkPos chunkPos(x, z);

    auto it = m_chunkPositions.find(chunkPos);
    if (it == m_chunkPositions.end()) {
        int blockX = x * 16 + 8;
        int blockZ = z * 16 + 8;

        bool ret = m_biomeSource->containsOnly(blockX, blockZ, m_featureBiomeRequirements->m_field8,
                                               *m_featureBiomeRequirements->m_biomes0);
        if (ret) {
            if (m_featureBiomeRequirements->m_biomes1 != nullptr)
                ret = m_biomeSource->containsOnly(blockX, blockZ, m_featureBiomeRequirements->m_field1A,
                                                  *m_featureBiomeRequirements->m_biomes1);
        }

        m_chunkPositions.at(chunkPos) = ret;
        return ret;
    }

    return it->second;
}

BiomeSource::BiomeSource() {
    init();
}

BiomeSource::BiomeSource(long long seed, LevelType* levelType, SuperflatConfig* superflatConfig,
                         BiomeSource::LayerOverrideSettings* settings) {
    init(seed, levelType, superflatConfig, nullptr, settings);
}

BiomeSource::BiomeSource(LevelData* levelData) {
    init(levelData->getSeed(), levelData->getGeneratorType(), levelData->getGeneratorOptions(), levelData,
         nullptr);
}

void BiomeSource::init() {
    InitializeCriticalSection(&m_mutexType);

    m_noiseBiomeLayer = nullptr;
    m_blockBiomeLayer = nullptr;

    m_biomeCache = new BiomeCache(this);

    m_possibleBiomes.push_back(Biome::FOREST);
    m_possibleBiomes.push_back(Biome::PLAINS);
    m_possibleBiomes.push_back(Biome::TAIGA);
    m_possibleBiomes.push_back(Biome::TAIGA_HILLS);
    m_possibleBiomes.push_back(Biome::FOREST_HILLS);
    m_possibleBiomes.push_back(Biome::JUNGLE);
    m_possibleBiomes.push_back(Biome::JUNGLE_HILLS);
}

void BiomeSource::init(long long seed, LevelType* levelType, SuperflatConfig* superflatConfig,
                       LevelData* levelData, BiomeSource::LayerOverrideSettings* settings) {
    init();

    arrayWithLength<std::shared_ptr<Layer>> layers
        = Layer::getDefaultLayers(seed, levelType, superflatConfig, levelData, settings);
    m_noiseBiomeLayer = layers[0];
    m_blockBiomeLayer = layers[1];

    delete[] layers.m_data;
}

void BiomeSource::update() {
    m_biomeCache->update();
}

bool BiomeSource::fjCouldSpawn(const FjFeatureBiomeRequirements* biomeRequirements, int x, int z) {
    for (CouldSpawnCache& couldSpawnCache : m_couldSpawnCaches) {
        if (couldSpawnCache.m_featureBiomeRequirements == biomeRequirements) {
            EnterCriticalSection(&m_mutexType);
            bool ret = couldSpawnCache.couldSpawn(x, z);
            LeaveCriticalSection(&m_mutexType);

            return ret;
        }
    }

    m_couldSpawnCaches.emplace_back(CouldSpawnCache(this, biomeRequirements));

    return fjCouldSpawn(biomeRequirements, x, z);
}

BiomeSource::~BiomeSource() {
    nn::os::FinalizeMutex(&m_mutexType);

    delete m_biomeCache;
}

Biome* BiomeSource::getBiome(const BlockPos& pos) {
    return this->getBiome(pos, nullptr);
}

Biome* BiomeSource::getBiome(const BlockPos& pos, Biome* biome) {
    return m_biomeCache->getBiome(pos.getX(), pos.getZ(), biome);
}

void BiomeSource::getRawBiomeBlock(arrayWithLength<Biome*>& biomes, int x, int z, int width,
                                   int depth) const {
    PIXBeginNamedEvent(0.0, "Setup");

    IntCache::releaseAll();
    biomes.resize(width * depth);

    PIXEndNamedEvent();

    PIXBeginNamedEvent(0.0, "Getting area");
    arrayWithLength<int> area = m_noiseBiomeLayer->getArea(x, z, width, depth);
    PIXEndNamedEvent();

    PIXBeginNamedEvent(0.0, "Copying values");
    for (int i = 0; i < width * depth; i++) {
        biomes[i] = Biome::getBiome(area[i], Biome::DEFAULT);
    }
    PIXEndNamedEvent();
}

void BiomeSource::getRawBiomeIndices(arrayWithLength<int>& biomes, int x, int z, int width, int depth) const {
    IntCache::releaseAll();

    arrayWithLength<int> area = m_noiseBiomeLayer->getArea(x, z, width, depth);

    for (int i = 0; i < width * depth; i++) {
        biomes[i] = area[i];
    }
}

void BiomeSource::getBiomeBlock(arrayWithLength<Biome*>& biomes, int x, int z, int width, int depth,
                                bool bl) const {
    PIXBeginNamedEvent(0.0, "Setup");

    IntCache::releaseAll();
    biomes.resize(width * depth);

    PIXEndNamedEvent();

    if (bl && width == 16 && depth == 16 && (x & 15) == 0 && (z & 15) == 0) {
        PIXBeginNamedEvent(0.0, "Copying cache");

        arrayWithLength<Biome*> biomeBlock = m_biomeCache->getBiomeBlockAt(x, z);
        System::arraycopy(biomeBlock, 0, &biomes, 0, width * depth);

        delete biomeBlock.m_data;

        PIXEndNamedEvent();
    } else {
        PIXBeginNamedEvent(0.0, "Getting area");
        arrayWithLength<int> area = m_blockBiomeLayer->getArea(x, z, width, depth);
        PIXEndNamedEvent();

        PIXBeginNamedEvent(0.0, "Copying values");
        for (int i = 0; i < width * depth; i++) {
            biomes[i] = Biome::getBiome(area[i], Biome::DEFAULT);
        }
        PIXEndNamedEvent();
    }
}

arrayWithLength<unsigned char> BiomeSource::getBiomeIndexBlock(int x, int z, int width, int depth) const {
    if (width == 16 && depth == 16 && (x & 15) == 0 && (z & 15) == 0) {
        return m_biomeCache->getBiomeIndexBlockAt(x, z);
    }

    arrayWithLength<unsigned char> biomes;
    getBiomeIndexBlock(biomes, x, z, width, depth, true);

    return biomes;
}

void BiomeSource::getBiomeIndexBlock(arrayWithLength<unsigned char>& biomes, int x, int z, int width,
                                     int depth, bool bl) const {
    IntCache::releaseAll();
    biomes.resize(width * depth);

    if (bl && width == 16 && depth == 16 && (x & 15) == 0 && (z & 15) == 0) {
        PIXBeginNamedEvent(0.0, "Copying cached block");
        arrayWithLength<unsigned char> biomeBlock = m_biomeCache->getBiomeIndexBlockAt(x, z);
        System::arraycopy(biomeBlock, 0, &biomes, 0, width * depth);
        PIXEndNamedEvent();
    } else {
        PIXBeginNamedEvent(0.0, "Getting area");
        arrayWithLength<int> area = m_blockBiomeLayer->getArea(x, z, width, depth);
        PIXEndNamedEvent();

        PIXBeginNamedEvent(0.0, "Copying values");
        for (int i = 0; i < width * depth; i++) {
            biomes[i] = area[i];
        }
        PIXEndNamedEvent();
    }
}

// NON_MATCHING | Score: 1065 (lower is better)
bool BiomeSource::containsOnly(int x, int z, int radius, const std::vector<Biome*>& biomes) {
    IntCache::releaseAll();
    int xPos = (x - radius) >> 2;
    int zPos = (z - radius) >> 2;
    int n = (x + radius) >> 2;
    int o = (z + radius) >> 2;
    int width = n - xPos + 1;
    int depth = o - zPos + 1;

    arrayWithLength<int> area = m_noiseBiomeLayer->getArea(xPos, zPos, width, depth);

    for (int i = 0; i < width * depth; i++) {
        Biome* biome = Biome::getBiome(area[i]);
        if (biomes[i] == biome) {
            return false;
        }
    }

    return true;
}

// NON_MATCHING | Score: 1915 (lower is better)
BlockPos* BiomeSource::findBiome(int x, int z, int radius, std::vector<Biome*> biomes, Random* random) {
    IntCache::releaseAll();
    int xPos = (x - radius) >> 2;
    int zPos = (z - radius) >> 2;
    int n = (x + radius) >> 2;
    int o = (z + radius) >> 2;
    int width = n - xPos + 1;
    int depth = o - zPos + 1;

    MemSect(50);
    arrayWithLength<int> area = m_noiseBiomeLayer->getArea(xPos, zPos, width, depth);
    BlockPos* blockPos = nullptr;

    int i = 0;
    for (int j = 0; j < width * depth; j++) {
        int blockX = (xPos + j % width) << 2;
        int blockZ = (zPos + j / width) << 2;
        Biome* biome = Biome::getBiome(area[j]);

        if (biomes[i] == biome && (blockPos == nullptr || random->nextInt(i + 1) == 0)) {
            delete blockPos;
            blockPos = new BlockPos(blockX, 0, blockZ);
            i++;
        }
    }

    MemSect(0);
    return blockPos;
}

bool BiomeSource::isFixedBiome() {
    return false;
}

Biome* BiomeSource::getFixedBiome() {
    return nullptr;
}
