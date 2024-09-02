#pragma once

#include <memory>

#include "Minecraft.World/level/storage/LevelSource.h"

class BlockPos;
class BlockState;
class LevelSettings;
class Direction;
class Player;
class SoundEvent;
class Entity;
class BlockEntity;
class Block;
class SoundSource {
public:
    enum ESoundSource {};
};
class LevelChunk;
class BoundingBox;
class CompoundTag;
class Packet;
class Random;

class Level : public LevelSource {
public:
    virtual void getBlockEntity(BlockPos const&) override;
    virtual void getLightColor(BlockPos const&, int, int) override;
    virtual void getBrightness(LightLayer::variety, BlockPos const&) override;
    virtual void getBrightness(BlockPos const&, int) override;
    virtual void getBrightness(BlockPos const&) override;
    virtual const BlockState* getBlockState(BlockPos const&) override;
    virtual void getBlockId(int, int, int) override;
    virtual void getBlockData(int, int, int) override;
    virtual void getBlock(BlockPos const&) override;
    virtual bool isEmptyBlock(BlockPos const&) override;
    virtual void getBiome(BlockPos const&) override;
    virtual void getBiomeSource() override;
    virtual void getMaxBuildHeight() override;
    virtual bool isAllEmpty() override;
    virtual void getDirectSignal(BlockPos const&, Direction const*) override;
    virtual void getGeneratorType() override;
    virtual ~Level() override;
    virtual void postConstruct();
    virtual void pure_virtual_1() = 0;
    virtual void initializeLevel(LevelSettings*);
    virtual void getServer();
    virtual void validateSpawn();
    virtual void pure_virtual_2() = 0;
    virtual bool isChunkGeneratedAt(int, int);
    virtual void setBlock(BlockPos const&, BlockState const*, int, bool);
    virtual void setData(BlockPos const&, int, int, bool);
    virtual void setData(int, int, int, int, int, bool);
    virtual void removeBlock(BlockPos const&);
    virtual void destroyBlock(BlockPos const&, bool);
    virtual void setBlockAndUpdate(BlockPos const&, BlockState const*);
    virtual void sendBlockUpdated(BlockPos const&, BlockState const*, BlockState const*, int, bool);
    virtual bool isBlockToBeTickedAt(BlockPos const&, Block*);
    virtual void getNeighbourBrightnesses(int*, LightLayer::variety, int, int, int);
    virtual void playSound(std::shared_ptr<Player>, BlockPos const&, SoundEvent const*, SoundSource::ESoundSource, float, float, float);
    virtual void playSound(std::shared_ptr<Player>, double, double, double, SoundEvent const*, SoundSource::ESoundSource, float, float, float);
    virtual void playLocalSound(double, double, double, SoundEvent const*, SoundSource::ESoundSource, float, float, bool, float);
    virtual void addGlobalEntity(std::shared_ptr<Entity>);
    virtual void addEntity(std::shared_ptr<Entity>);
    virtual void entityAdded(std::shared_ptr<Entity>);
    virtual void entityRemoved(std::shared_ptr<Entity>);
    virtual void playerRemoved(std::shared_ptr<Entity>);
    virtual void removeEntity(std::shared_ptr<Entity>);
    virtual void hasTickNextTick(BlockPos const&, Block*);
    virtual void addToTickNextTick(BlockPos const&, Block*, int);
    virtual void addToTickNextTick(BlockPos const&, Block*, int, int);
    virtual void forceAddBlockTick(BlockPos const&, Block*, int, int);
    virtual void tickEntities();
    virtual void tickServerPlayers();
    virtual void tick(std::shared_ptr<Entity>, bool);
    virtual void sub_71002017F0();
    virtual void tick();
    virtual void blockEntityAddedExtra(std::shared_ptr<BlockEntity>);
    virtual void blockEntityRemovedExtra(std::shared_ptr<BlockEntity>);
    virtual void tickWeather(bool);
    virtual void buildAndPrepareChunksToPoll();
    virtual void pure_virtual_3() = 0;
    virtual void tickClientSideBlocks(int, int, LevelChunk*);
    virtual void tickBlocks();
    virtual void tickPendingTicks(bool);
    virtual void fetchTicksInChunk(LevelChunk*, bool);
    virtual void fetchTicksInArea(BoundingBox*, bool);
    virtual void getEntity(int);
    virtual void addEntities(std::vector<std::shared_ptr<Entity>, std::allocator<std::shared_ptr<Entity>>>*);
    virtual void removeEntities(std::vector<std::shared_ptr<Entity>, std::allocator<std::shared_ptr<Entity>>>*);
    virtual void disconnect(bool);
    virtual void mayInteract(std::shared_ptr<Player>, BlockPos const&, Block*);
    virtual void broadcastEntityEvent(std::shared_ptr<Entity>, unsigned int, int);
    virtual void blockEvent(BlockPos const&, Block*, int, int);
    virtual void updateSleepingPlayerList();
    virtual void createFireworks(double, double, double, double, double, double, CompoundTag*);
    virtual void pure_virtual_4() = 0;
    virtual void updateNeighbourForOutputSignal(BlockPos const&, Block*);
    virtual void sendPacketToServer(std::shared_ptr<Packet>);
    virtual void findNearestMapFeature(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t>> const&, BlockPos const&, bool);
    virtual void newPrimedTntAllowed();
    virtual void newFallingBlockAllowed();
    virtual void explodeNextEnderCrystal();
    virtual void AllPlayersAreSleeping();

    bool isOutsideBuildHeight(BlockPos const&);
    LevelChunk* getChunkAt(BlockPos const&);

    void instaTick(BlockPos const&, BlockState const*, Random&);
};
