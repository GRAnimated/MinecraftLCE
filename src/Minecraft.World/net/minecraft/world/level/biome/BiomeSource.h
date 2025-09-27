#pragma once

#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/level/chunk/ChunkPos.h"
#include "nn/os/os_MutexTypes.h"
#include <memory>
#include <unordered_map>

class BlockPos;
class Biome;
class Random;
class Layer;
class BiomeCache;
class SuperflatConfig;
class LevelType;
class LevelData;
class CustomizableSourceSettings;
class FjFeatureBiomeRequirements;

class BiomeSource {
public:
    // These could be completely wrong, and are just placeholders.
    // I plan to check this again later - Azalea
    enum eBiomeGenerationScale {
        eBiomeGenerationScale_CLASSIC,
        eBiomeGenerationScale_SMALL,
        eBiomeGenerationScale_MEDIUM,
        eBiomeGenerationScale_LARGE
    };

    class LayerOverrideSettings {
    public:
        LayerOverrideSettings();

        void SetGenerationScale(eBiomeGenerationScale scale);

        void SetZoomedDisplay(int x, int z);
        bool isZoomed();

        unsigned char GetZoomLevel();

        bool ZoomIn();
        int GetZoomedCentreX();
        int GetZoomedCentreZ();
        bool ZoomOut();

        int getBiomeIndex(int x, int z);
        void NullBiomeSection(int x, int z, int width, int depth);

        int GetBiomeSectionWidth();
        void UpdateBiomeMapPixelsInRegion(unsigned int* mapPixels, unsigned int x, unsigned int z,
                                          unsigned int width, unsigned int depth, bool& bl0, bool bl1);

        BlockPos GetCursorBlockPos(float x, float z);
        long long GetSeed();
        int GetImageWidth();
        eBiomeGenerationScale GetGenerationScale();
        unsigned char GetBiomeScale();
        int GetZoomedCentreXPercent();
        int GetZoomedCentreZPercent();
        int GetCentreXChunk();
        int GetCentreZChunk();
        Biome* GetBiomeAt(float x, float z);

        Random* mRandom;
        long long mSeed;
        int mXZSize;
        int mImageWidth;
        int field_18;
        int field_1C;
        int mBiomeSectionWidth;
        int field_24;
        arrayWithLength<Biome*> mBiomes;
        unsigned char field_38;
        eBiomeGenerationScale mGenScale;
        int field_40;
        int mBiomeScale;
        int mCentreXChunk;
        int mCentreZChunk;
        unsigned char mZoomLevel;
        int mZoomX;
        int mZoomZ;
        nn::os::MutexType mMutexType;
    };

    class CouldSpawnCache {
    public:
        CouldSpawnCache(BiomeSource* biomeSource,
                        const FjFeatureBiomeRequirements* featureBiomeRequirements);  // 4A0B0

        bool couldSpawn(int x, int z);

        std::unordered_map<ChunkPos, bool, ChunkPosKeyHash, ChunkPosKeyEq> mChunkPositions;
        BiomeSource* mBiomeSource;
        const FjFeatureBiomeRequirements* mFeatureBiomeRequirements;
    };

    static long long findSeed(LevelType* levelType);
    static bool getIsMatch(arrayWithLength<int>, float*, float*);  // 49E44
    static void getFracs(arrayWithLength<int>, float*, float*);    // 49EF8
    static unsigned char getBiomeGroup(int);                       // 4A038 (?)

    BiomeSource();
    BiomeSource(long long seed, LevelType* levelType, SuperflatConfig* superflatConfig,
                LayerOverrideSettings* settings);
    BiomeSource(LevelData* levelData);

    void init();
    void init(long long seed, LevelType* levelType, SuperflatConfig* superflatConfig, LevelData* levelData,
              LayerOverrideSettings* settings);
    void update();
    bool fjCouldSpawn(const FjFeatureBiomeRequirements* biomeRequirements, int x, int z);  // 4A408

    virtual ~BiomeSource();
    virtual Biome* getBiome(const BlockPos& pos);
    virtual Biome* getBiome(const BlockPos& pos, Biome* biome);
    virtual void getRawBiomeBlock(arrayWithLength<Biome*>& biomes, int x, int z, int width, int depth) const;
    virtual void getRawBiomeIndices(arrayWithLength<int>& biomes, int x, int z, int width, int depth) const;
    virtual void getBiomeBlock(arrayWithLength<Biome*>& biomes, int x, int z, int width, int depth,
                               bool bl) const;
    virtual arrayWithLength<unsigned char> getBiomeIndexBlock(int x, int z, int width, int depth) const;
    virtual void getBiomeIndexBlock(arrayWithLength<unsigned char>& biomes, int x, int z, int width,
                                    int depth, bool bl) const;
    virtual bool containsOnly(int x, int z, int radius, const std::vector<Biome*>& biomes);
    virtual BlockPos* findBiome(int x, int z, int radius, std::vector<Biome*> biomes, Random* random);
    virtual bool isFixedBiome();
    virtual Biome* getFixedBiome();

    std::shared_ptr<Layer> mNoiseBiomeLayer;
    std::shared_ptr<Layer> mBlockBiomeLayer;
    BiomeCache* mBiomeCache;
    std::vector<Biome*> mPossibleBiomes;
    nn::os::MutexType mMutexType;
    std::vector<CouldSpawnCache> mCouldSpawnCaches;
};
