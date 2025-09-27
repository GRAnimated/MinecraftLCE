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
    field_38 = 0;
    mGenScale = static_cast<eBiomeGenerationScale>(-1);

    mRandom = new Random(System::processTimeInNanoSecs());

    long seed = mRandom->nextLong();
    field_40 = 6;
    mBiomeScale = 0;
    mSeed = seed;
    mXZSize = 54;
    mImageWidth = 864;
    mZoomLevel = 0;
    mZoomX = 0;
    mZoomZ = 0;
    mCentreXChunk = 0;
    mCentreZChunk = 0;
    field_18 = 432;
    field_1C = 12;
    mBiomeSectionWidth = 72;
    field_24 = 36;

    InitializeCriticalSection(&mMutexType);
    EnterCriticalSection(&mMutexType);

    mBiomes = {static_cast<unsigned int>(mImageWidth * mImageWidth), true};

    LeaveCriticalSection(&mMutexType);
}

void BiomeSource::LayerOverrideSettings::SetGenerationScale(BiomeSource::eBiomeGenerationScale scale) {
    mBiomeScale = scale;
}

bool BiomeSource::LayerOverrideSettings::isZoomed() {
    return mZoomLevel != 0;
}

unsigned char BiomeSource::LayerOverrideSettings::GetZoomLevel() {
    return mZoomLevel;
}

// NON_MATCHING | Score: 560 (lower is better)
// If I knew assembly, I bet I could figure this one out.
// Dw tho, I'll learn assembly soon - Azalea
bool BiomeSource::LayerOverrideSettings::ZoomIn() {
    if (mZoomLevel != 0)
        return false;

    int zoomCentreX = GetZoomedCentreX();
    int zoomCentreZ = GetZoomedCentreZ();

    mZoomLevel++;

    SetZoomedDisplay(zoomCentreX, zoomCentreZ);
    return true;
}

int BiomeSource::LayerOverrideSettings::GetZoomedCentreX() {
    if (!isZoomed())
        return 0;

    int level = (int)std::pow(2.0, mZoomLevel + 1.0);
    return field_18 * mZoomX / level;
}

int BiomeSource::LayerOverrideSettings::GetZoomedCentreZ() {
    if (!isZoomed())
        return 0;

    int level = (int)std::pow(2.0, mZoomLevel + 1.0);
    return field_18 * mZoomZ / level;
}

bool BiomeSource::LayerOverrideSettings::ZoomOut() {
    if (mZoomLevel == 0)
        return false;

    int zoomCentreX = GetZoomedCentreX();
    int zoomCentreZ = GetZoomedCentreZ();

    mZoomLevel--;

    SetZoomedDisplay(zoomCentreX, zoomCentreZ);
    return true;
}

int BiomeSource::LayerOverrideSettings::getBiomeIndex(int x, int z) {
    return x + mImageWidth * z;
}

// NON_MATCHING | Score: 300 (lower is better)
// Another one that knowing assembly would be good for - Azalea
void BiomeSource::LayerOverrideSettings::NullBiomeSection(int x, int z, int width, int depth) {
    unsigned long len = z;
    for (int i = width; i < depth + width; i++) {
        Biome* biome = mBiomes[x + mImageWidth * i];
        memset((void*)biome, 0, len);
    }
}

int BiomeSource::LayerOverrideSettings::GetBiomeSectionWidth() {
    return mBiomeSectionWidth;
}

BlockPos BiomeSource::LayerOverrideSettings::GetCursorBlockPos(float x, float z) {
    int zoomLevel = (int)std::pow(2.0, mZoomLevel);
    int v6 = field_18 / zoomLevel;

    int centreX = 0;
    int centreZ = 0;
    if (isZoomed()) {
        int level = (int)std::pow(2.0, mZoomLevel + 1.0);
        centreX = field_18 * mZoomX / level;
        centreZ = field_18 * mZoomZ / level;
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
    return mSeed;
}

int BiomeSource::LayerOverrideSettings::GetImageWidth() {
    return mImageWidth;
}

BiomeSource::eBiomeGenerationScale BiomeSource::LayerOverrideSettings::GetGenerationScale() {
    return static_cast<eBiomeGenerationScale>(mBiomeScale);
}

unsigned char BiomeSource::LayerOverrideSettings::GetBiomeScale() {
    return mBiomeScale;
}

int BiomeSource::LayerOverrideSettings::GetZoomedCentreXPercent() {
    if (!isZoomed())
        return 0;

    int level = (int)std::pow(2.0, mZoomLevel + 1.0);
    return mZoomX * 100 / level;
}

int BiomeSource::LayerOverrideSettings::GetZoomedCentreZPercent() {
    if (!isZoomed())
        return 0;

    int level = (int)std::pow(2.0, mZoomLevel + 1.0);
    return mZoomZ * 100 / level;
}

int BiomeSource::LayerOverrideSettings::GetCentreXChunk() {
    return mCentreXChunk;
}

int BiomeSource::LayerOverrideSettings::GetCentreZChunk() {
    return mCentreZChunk;
}

// NON_MATCHING | Score: 540 (lower is better)
Biome* BiomeSource::LayerOverrideSettings::GetBiomeAt(float x, float z) {
    BlockPos pos = GetCursorBlockPos(x, z);

    int xPos = field_18 + pos.getX();
    if (xPos < mImageWidth - 1)
        xPos = mImageWidth - 1;

    int zPos = field_18 + pos.getZ();
    if (zPos >= mImageWidth - 1)
        zPos = mImageWidth - 1;

    unsigned int index = getBiomeIndex(xPos, zPos);
    return mBiomes[index];
}

// NON_MATCHING | Score: 1425 (lower is better)
// Something I did messed this up. I'll have to check again later - Azalea
BiomeSource::CouldSpawnCache::CouldSpawnCache(BiomeSource* biomeSource,
                                              const FjFeatureBiomeRequirements* featureBiomeRequirements) {
    mChunkPositions = {};
    mBiomeSource = biomeSource;
    mFeatureBiomeRequirements = featureBiomeRequirements;
}

bool BiomeSource::CouldSpawnCache::couldSpawn(int x, int z) {
    ChunkPos chunkPos(x, z);

    auto it = mChunkPositions.find(chunkPos);
    if (it == mChunkPositions.end()) {
        int blockX = x * 16 + 8;
        int blockZ = z * 16 + 8;

        bool ret = mBiomeSource->containsOnly(blockX, blockZ, mFeatureBiomeRequirements->field_8,
                                              *mFeatureBiomeRequirements->mBiomes0);
        if (ret) {
            if (mFeatureBiomeRequirements->mBiomes1 != nullptr)
                ret = mBiomeSource->containsOnly(blockX, blockZ, mFeatureBiomeRequirements->field_1A,
                                                 *mFeatureBiomeRequirements->mBiomes1);
        }

        mChunkPositions.at(chunkPos) = ret;
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
    InitializeCriticalSection(&mMutexType);

    mNoiseBiomeLayer = nullptr;
    mBlockBiomeLayer = nullptr;

    mBiomeCache = new BiomeCache(this);

    mPossibleBiomes.push_back(Biome::FOREST);
    mPossibleBiomes.push_back(Biome::PLAINS);
    mPossibleBiomes.push_back(Biome::TAIGA);
    mPossibleBiomes.push_back(Biome::TAIGA_HILLS);
    mPossibleBiomes.push_back(Biome::FOREST_HILLS);
    mPossibleBiomes.push_back(Biome::JUNGLE);
    mPossibleBiomes.push_back(Biome::JUNGLE_HILLS);
}

void BiomeSource::init(long long seed, LevelType* levelType, SuperflatConfig* superflatConfig,
                       LevelData* levelData, BiomeSource::LayerOverrideSettings* settings) {
    init();

    arrayWithLength<std::shared_ptr<Layer>> layers
        = Layer::getDefaultLayers(seed, levelType, superflatConfig, levelData, settings);
    mNoiseBiomeLayer = layers[0];
    mBlockBiomeLayer = layers[1];

    delete[] layers.data;
}

void BiomeSource::update() {
    mBiomeCache->update();
}

bool BiomeSource::fjCouldSpawn(const FjFeatureBiomeRequirements* biomeRequirements, int x, int z) {
    for (CouldSpawnCache& couldSpawnCache : mCouldSpawnCaches) {
        if (couldSpawnCache.mFeatureBiomeRequirements == biomeRequirements) {
            EnterCriticalSection(&mMutexType);
            bool ret = couldSpawnCache.couldSpawn(x, z);
            LeaveCriticalSection(&mMutexType);

            return ret;
        }
    }

    mCouldSpawnCaches.emplace_back(CouldSpawnCache(this, biomeRequirements));

    return fjCouldSpawn(biomeRequirements, x, z);
}

BiomeSource::~BiomeSource() {
    nn::os::FinalizeMutex(&mMutexType);

    delete mBiomeCache;
}

Biome* BiomeSource::getBiome(const BlockPos& pos) {
    return this->getBiome(pos, nullptr);
}

Biome* BiomeSource::getBiome(const BlockPos& pos, Biome* biome) {
    return mBiomeCache->getBiome(pos.getX(), pos.getZ(), biome);
}

void BiomeSource::getRawBiomeBlock(arrayWithLength<Biome*>& biomes, int x, int z, int width,
                                   int depth) const {
    PIXBeginNamedEvent(0.0, "Setup");

    IntCache::releaseAll();
    biomes.resize(width * depth);

    PIXEndNamedEvent();

    PIXBeginNamedEvent(0.0, "Getting area");
    arrayWithLength<int> area = mNoiseBiomeLayer->getArea(x, z, width, depth);
    PIXEndNamedEvent();

    PIXBeginNamedEvent(0.0, "Copying values");
    for (int i = 0; i < width * depth; i++) {
        biomes[i] = Biome::getBiome(area[i], Biome::DEFAULT);
    }
    PIXEndNamedEvent();
}

void BiomeSource::getRawBiomeIndices(arrayWithLength<int>& biomes, int x, int z, int width, int depth) const {
    IntCache::releaseAll();

    arrayWithLength<int> area = mNoiseBiomeLayer->getArea(x, z, width, depth);

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

        arrayWithLength<Biome*> biomeBlock = mBiomeCache->getBiomeBlockAt(x, z);
        System::arraycopy(biomeBlock, 0, &biomes, 0, width * depth);

        delete biomeBlock.data;

        PIXEndNamedEvent();
    } else {
        PIXBeginNamedEvent(0.0, "Getting area");
        arrayWithLength<int> area = mBlockBiomeLayer->getArea(x, z, width, depth);
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
        return mBiomeCache->getBiomeIndexBlockAt(x, z);
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
        arrayWithLength<unsigned char> biomeBlock = mBiomeCache->getBiomeIndexBlockAt(x, z);
        System::arraycopy(biomeBlock, 0, &biomes, 0, width * depth);
        PIXEndNamedEvent();
    } else {
        PIXBeginNamedEvent(0.0, "Getting area");
        arrayWithLength<int> area = mBlockBiomeLayer->getArea(x, z, width, depth);
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

    arrayWithLength<int> area = mNoiseBiomeLayer->getArea(xPos, zPos, width, depth);

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
    arrayWithLength<int> area = mNoiseBiomeLayer->getArea(xPos, zPos, width, depth);
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
