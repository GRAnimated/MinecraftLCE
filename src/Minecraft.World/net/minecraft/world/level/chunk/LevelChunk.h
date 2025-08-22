#pragma once

#include "net/minecraft/core/System.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/level/LightLayer.h"
#include "net/minecraft/world/level/chunk/ChunkPos.h"
#include "net/minecraft/world/level/storage/block/CompressedBlockStorage.h"
#include "net/minecraft/world/level/storage/data/SparseDataStorage.h"
#include "net/minecraft/world/level/storage/light/SparseLightStorage.h"

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

class LevelChunk {
public:
    static bool touchedSky;  // Name from b1.2_02

    LevelChunk(Level*, ChunkPrimer*, int, int);

    enum EntityCreationType {};

    void staticCtor();

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
    virtual void setData(int, int, int, int, int, bool*);
    virtual void setBlock(const BlockPos&, const BlockState*);
    virtual void setBlockAndData(int, int, int, int, int, bool);
    virtual int getBrightness(LightLayer::variety, const BlockPos&);
    virtual void getNeighbourBrightnesses(int*, LightLayer::variety, int, int, int);
    virtual void setBrightness(LightLayer::variety, const BlockPos&, int);
    virtual int getRawBrightness(const BlockPos&, int);
    virtual void addEntity(std::shared_ptr<Entity>);
    virtual void removeEntity(std::shared_ptr<Entity>);
    virtual void removeEntity(std::shared_ptr<Entity>, int);
    virtual bool isSkyLit(const BlockPos&);
    virtual void getBlockEntity(const BlockPos&, LevelChunk::EntityCreationType);
    virtual void addBlockEntity(std::shared_ptr<BlockEntity>);
    virtual void setBlockEntity(const BlockPos&, std::shared_ptr<BlockEntity>);
    virtual void removeBlockEntity(const BlockPos&);
    virtual void load(bool);
    virtual void unload(bool, bool);
    virtual void containsPlayer();
    virtual void field_160();
    virtual void markUnsaved();
    virtual void getEntities(std::shared_ptr<Entity>, AABB const*, std::vector<std::shared_ptr<Entity>>&,
                             const Predicate<std::shared_ptr<Entity>>*);
    virtual void getEntitiesOfClass(const std::type_info&, AABB const*, std::vector<std::shared_ptr<Entity>>&,
                                    const Predicate<std::shared_ptr<Entity>>*, bool);
    virtual void countEntities();
    virtual void shouldSave(bool);
    virtual void getBlocksAndData(arrayWithLength<unsigned char>*, int, int, int, int, int, int, int, bool);
    virtual void setBlocksAndData(arrayWithLength<unsigned char>, int, int, int, int, int, int, int, bool);
    virtual void testSetBlocksAndData(arrayWithLength<unsigned char>, int, int, int, int, int, int, int);
    virtual void getRandom(long long);
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

    int getBlockId(int, int, int);
    int getData(int, int, int);

    char padding_0[24];
    CompressedBlockStorage* mBlockDataLower;  // Y0-Y127
    CompressedBlockStorage* mBlockDataUpper;  // Y128-Y255

    char unk[400];

    SparseDataStorage* mDataDataLower;         // Y0-Y127
    SparseDataStorage* mDataDataUpper;         // Y128-Y255
    SparseLightStorage* mSkyLightDataLower;    // Y0-Y127
    SparseLightStorage* mSkyLightDataUpper;    // Y128-Y255
    SparseLightStorage* mBlockLightDataLower;  // Y0-Y127
    SparseLightStorage* mBlockLightDataUpper;  // Y128-Y255
    char padding_480[24];
    int xPos;
    int zPos;
    char unk2[14];
    std::unordered_map<BlockPos, std::shared_ptr<BlockEntity>>* blockEntities;
    char unk3[32];
    short biomeCount;
    char unk4[42];
    long inhabitedTime;
    char unk5[86];
};
