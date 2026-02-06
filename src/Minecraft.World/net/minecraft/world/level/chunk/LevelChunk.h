#pragma once

#include "deque"
#include "net/minecraft/core/System.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/level/LightLayer.h"
#include "net/minecraft/world/level/chunk/ChunkPos.h"
#include "net/minecraft/world/level/storage/block/CompressedBlockStorage.h"
#include "net/minecraft/world/level/storage/data/SparseDataStorage.h"
#include "net/minecraft/world/level/storage/light/SparseLightStorage.h"
#include "net/minecraft/core/BlockPos.h"

#include <memory>
#include <unordered_map>

template <typename T>
class Predicate;

class Block;
class BlockPos;
class BlockState;
class BlockEntity;
class Level;
class AABB;
class BiomeSource;
class Biome;
class Entity;
class ChunkPrimer;
class DataOutputStream;
class ChunkSource;
class ChunkGenerator;

class LevelChunk {
public:
    static bool touchedSky;  // Name from b1.2_02

    // TODO put this somewhere better, maybe CompressedBlockStorage if used there
#define INDEX_BLOCK_ARRAY(x, y, z) y | (x << 11) | (z << 7)

    class BlockChange {};

    enum DECOMP_HELPER PopulationFlags : int {
        FLAG_TERRAIN_POPULATED = 0x400
    };

    LevelChunk(Level*, ChunkPrimer*, int, int);
    LevelChunk(Level*, int, int);

    enum EntityCreationType {};

    static void staticCtor();

    void tick(bool);
    void recheckGaps(bool local);
    void postProcess();

    std::shared_ptr<BlockEntity> createBlockEntity(const BlockPos &pos);

    static nn::os::MutexType mMutex_710178c150;
    static nn::os::MutexType mMutex_710178c170;
    static nn::os::MutexType mMutex_710178c190;

    virtual void setBlockData(arrayWithLength<unsigned char>);
    virtual void getBlockData(arrayWithLength<unsigned char>);
    virtual void getBlockDataRange(arrayWithLength<unsigned char>, int, int);
    virtual void setDataData(arrayWithLength<unsigned char>);
    virtual void getDataData(arrayWithLength<unsigned char>);
    virtual void getDataDataRange(arrayWithLength<unsigned char>, int, int);
    virtual void getSkyLightData(arrayWithLength<unsigned char>);
    virtual void getBlockLightData(arrayWithLength<unsigned char>);
    virtual void setSkyLightData(arrayWithLength<unsigned char>);
    virtual void setBlockLightData(arrayWithLength<unsigned char>);
    virtual void reSyncLighting();
    virtual void reSyncLightingNearby();
    virtual void dropLighting();
    virtual void init(Level*, int, int);
    virtual ~LevelChunk();
    virtual void isAt(int, int);
    virtual int getHeightmap(int, int);
    virtual void recalcBlockLights();
    virtual void recalcHeightmapOnly();
    virtual void recalcHeightmap();
    virtual void lightLava();
    virtual void getBlockLightBlock(const BlockPos&);
    virtual Block* getBlock(const BlockPos&);
    virtual const BlockState* getBlockState(const BlockPos&);
    virtual void getData(const BlockPos&);
    virtual bool setData(int, int, int, int, int, bool*);
    virtual const BlockState* setBlock(const BlockPos&, const BlockState*);
    virtual bool setBlockAndData(int, int, int, int, int, bool);
    virtual int getBrightness(LightLayer::variety, const BlockPos&);
    virtual void getNeighbourBrightnesses(int*, LightLayer::variety, int, int, int);
    virtual void setBrightness(LightLayer::variety, const BlockPos&, int);
    virtual int getRawBrightness(const BlockPos&, int);
    virtual void addEntity(std::shared_ptr<Entity>);
    virtual void removeEntity(std::shared_ptr<Entity>);
    virtual void removeEntity(std::shared_ptr<Entity>, int);
    virtual bool isSkyLit(const BlockPos&);
    virtual std::shared_ptr<BlockEntity> getBlockEntity(const BlockPos&, LevelChunk::EntityCreationType);
    virtual void addBlockEntity(std::shared_ptr<BlockEntity>);
    virtual void setBlockEntity(const BlockPos&, std::shared_ptr<BlockEntity>);
    virtual void removeBlockEntity(const BlockPos&);
    virtual void load(bool);
    virtual void unload(bool, bool);
    virtual bool containsPlayer();
    virtual bool
    DECOMP_getUnknownField();  // NAME NOT KNOWN, don't want it to appear like it is in IDA either
    virtual void markUnsaved();
    virtual void getEntities(std::shared_ptr<Entity>, AABB const*, std::vector<std::shared_ptr<Entity>>&,
                             const Predicate<std::shared_ptr<Entity>>*);
    virtual void getEntitiesOfClass(const std::type_info&, AABB const*, std::vector<std::shared_ptr<Entity>>&,
                                    const Predicate<std::shared_ptr<Entity>>*, bool);
    virtual int countEntities();
    virtual bool shouldSave(bool);
    virtual void getBlocksAndData(arrayWithLength<unsigned char>*, int, int, int, int, int, int, int, bool);
    virtual void setBlocksAndData(arrayWithLength<unsigned char>, int, int, int, int, int, int, int, bool);
    virtual bool testSetBlocksAndData(arrayWithLength<unsigned char>, int, int, int, int, int, int, int);
    virtual Random* getRandom(long long);
    virtual bool isEmpty();
    virtual Biome* getBiome(const BlockPos&, BiomeSource*);
    virtual void compressLighting();
    virtual void compressBlocks();
    virtual void compressData();
    virtual void getReorderedBlocksAndData(int, int, int, int, int&, int);

    // are these meant to be virtual?
    arrayWithLength<unsigned char> getHeightmap();
    arrayWithLength<unsigned char> getHeightmap(BlockPos& pos);
    arrayWithLength<unsigned char> getBiomes();
    void writeCompressedBlockData(DataOutputStream* out);
    void writeCompressedDataData(DataOutputStream* out);
    void writeCompressedSkyLightData(DataOutputStream* out);
    void writeCompressedBlockLightData(DataOutputStream* out);
    ChunkPos getPos();
    bool isTerrainPopulated();
    Block* GetBlock(CompressedBlockStorage* storage, int x, int y, int z);
    bool IsInvalid();
    void flagPostProcessComplete(short);
    void checkPostProcess(ChunkSource*, ChunkGenerator*);
    void checkChests(ChunkSource*, int, int);
    void setLastSaveTime(long long);

    int getBlockId(int, int, int);
    int getData(int, int, int);

    char padding_0[24];
    CompressedBlockStorage* mBlockDataLower;  // Y0-Y127
    CompressedBlockStorage* mBlockDataUpper;  // Y128-Y255

    char unk[391];
    Level* m_level;

    SparseDataStorage* mDataDataLower;         // Y0-Y127
    SparseDataStorage* mDataDataUpper;         // Y128-Y255
    SparseLightStorage* mSkyLightDataLower;    // Y0-Y127
    SparseLightStorage* mSkyLightDataUpper;    // Y128-Y255
    SparseLightStorage* mBlockLightDataLower;  // Y0-Y127
    SparseLightStorage* mBlockLightDataUpper;  // Y128-Y255
    char padding_480[24];
    int mXPos;
    int mZPos;
    bool m_tickSkylight; // guessed, could be skylightDirty maybe?
    char unk2[13];
    std::unordered_map<BlockPos, std::shared_ptr<BlockEntity>>* mBlockEntities;
    char unk3[32];
    short m_populatedFlags;
    char unk4[13];
    bool unk9;
    bool m_hasPostProcessed;
    bool unk11;
    bool unk12;
    bool unk6;
    char unk7[25];
    long mInhabitedTime;
    bool unk8;
    // char unk5[85]; // 728 with 85
    char unk5[30];
    std::deque<BlockPos> m_blockEntityPosTickQueue;
    char unk13[8];
};
