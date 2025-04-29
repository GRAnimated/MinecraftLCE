#pragma once

#include "Minecraft.World/ArrayWithLength.h"
#include "Minecraft.World/level/LightLayer.h"
#include "Minecraft.World/level/chunk/ChunkPos.h"
#include "Minecraft.World/level/storage/data/SparseDataStorage.h"
#include "Minecraft.World/level/storage/light/SparseLightStorage.h"
#include "Minecraft.World/level/storage/block/CompressedBlockStorage.h"


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
class Entity;
class ChunkPrimer;
class DataOutputStream;

class LevelChunk {
public:
    LevelChunk(Level*, ChunkPrimer*, int, int);

    enum EntityCreationType {};

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
    virtual arrayWithLength<unsigned char> getHeightmap(int, int);
    virtual void recalcBlockLights();
    virtual void recalcHeightmapOnly();
    virtual void recalcHeightmap();
    virtual void lightLava();
    virtual void getBlockLightBlock(BlockPos const&);
    virtual Block* getBlock(BlockPos const&);
    virtual const BlockState* getBlockState(BlockPos const&);
    virtual void getData(BlockPos const&);
    virtual void setData(int, int, int, int, int, bool*);
    virtual void setBlock(BlockPos const&, BlockState const*);
    virtual void setBlockAndData(int, int, int, int, int, bool);
    virtual void getBrightness(LightLayer::variety, BlockPos const&);
    virtual void getNeighbourBrightnesses(int*, LightLayer::variety, int, int, int);
    virtual void setBrightness(LightLayer::variety, BlockPos const&, int);
    virtual void getRawBrightness(BlockPos const&, int);
    virtual void addEntity(std::shared_ptr<Entity>);
    virtual void removeEntity(std::shared_ptr<Entity>);
    virtual void removeEntity(std::shared_ptr<Entity>, int);
    virtual void isSkyLit(BlockPos const&);
    virtual void getBlockEntity(BlockPos const&, LevelChunk::EntityCreationType);
    virtual void addBlockEntity(std::shared_ptr<BlockEntity>);
    virtual void setBlockEntity(BlockPos const&, std::shared_ptr<BlockEntity>);
    virtual void removeBlockEntity(BlockPos const&);
    virtual void load(bool);
    virtual void unload(bool, bool);
    virtual void containsPlayer();
    virtual void markUnsaved();
    virtual void getEntities(std::shared_ptr<Entity>, AABB const*, std::vector<std::shared_ptr<Entity>>&,
                             Predicate<std::shared_ptr<Entity>> const*);
    virtual void getEntitiesOfClass(std::type_info const&, AABB const*, std::vector<std::shared_ptr<Entity>>&,
                                    Predicate<std::shared_ptr<Entity>> const*, bool);
    virtual void countEntities();
    virtual void shouldSave(bool);
    virtual void getBlocksAndData(arrayWithLength<unsigned char>*, int, int, int, int, int, int, int, bool);
    virtual void setBlocksAndData(arrayWithLength<unsigned char>, int, int, int, int, int, int, int, bool);
    virtual void testSetBlocksAndData(arrayWithLength<unsigned char>, int, int, int, int, int, int, int);
    virtual void getRandom(long long);
    virtual void isEmpty();
    virtual void getBiome(BlockPos const&, BiomeSource*);
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

    char padding_0[24];
    CompressedBlockStorage *blockData1;
    CompressedBlockStorage *blockData2;
    char unk[400];
    SparseDataStorage *dataData1;
    SparseDataStorage *dataData2;
    SparseLightStorage *skyLightData1;
    SparseLightStorage *skyLightData2;
    SparseLightStorage *blockLightData1;
    SparseLightStorage *blockLightData2;
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