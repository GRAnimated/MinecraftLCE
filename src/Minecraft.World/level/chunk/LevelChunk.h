#pragma once

#include "Minecraft.World/ArrayWithLength.h"
#include "Minecraft.World/level/LightLayer.h"

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
    virtual void getHeightmap(int, int);
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

    char unk[520];
    int x; // GUESSED
    int z; // GUESSED
    char unk2[188];
};