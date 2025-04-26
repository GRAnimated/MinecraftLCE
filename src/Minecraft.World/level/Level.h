#pragma once

#include <memory>
#include <vector>

#include "Minecraft.World/ArrayWithLength.h"
#include "Minecraft.World/level/GameRules.h"
#include "Minecraft.World/level/storage/LevelSource.h"
#include "Minecraft.World/sounds/SoundSource.h"

class TickNextTickData;
class BlockPos;
class BlockState;
class LevelSettings;
class Direction;
class Difficulty;
class Player;
class SoundEvent;
class Entity;
class BlockEntity;
class Block;
class LevelChunk;
class LevelStorage;
class LevelData;
class Dimension;
class BoundingBox;
class CompoundTag;
class Packet;
class Random;
class WorldBorder;
class ParticleType;

class Level : public LevelSource {
public:
    Level(std::shared_ptr<LevelStorage>, LevelData*, Dimension*, bool);

    virtual void getBlockEntity(BlockPos const&) override;
    virtual void getLightColor(BlockPos const&, int, int) override;
    virtual void getBrightness(LightLayer::variety, BlockPos const&) override;
    virtual void getBrightness(BlockPos const&, int) override;
    virtual void getBrightness(BlockPos const&) override;
    virtual const BlockState* getBlockState(BlockPos const&) override;
    virtual void getBlockId(int, int, int) override;
    virtual void getBlockData(int, int, int) override;
    virtual Block* getBlock(BlockPos const&) override;
    virtual bool isEmptyBlock(BlockPos const&) override;
    virtual Biome* getBiome(BlockPos const&) override;
    virtual BiomeSource* getBiomeSource() override;
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
    virtual void playSound(std::shared_ptr<Player>, BlockPos const&, SoundEvent const*,
                           SoundSource::ESoundSource, float, float, float);
    virtual void playSound(std::shared_ptr<Player>, double, double, double, SoundEvent const*,
                           SoundSource::ESoundSource, float, float, float);
    virtual void playLocalSound(double, double, double, SoundEvent const*, SoundSource::ESoundSource, float,
                                float, bool, float);
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
    virtual std::vector<TickNextTickData*>* fetchTicksInChunk(LevelChunk*, bool);
    virtual std::vector<TickNextTickData*>* fetchTicksInArea(BoundingBox*, bool);
    virtual void getEntity(int);
    virtual void addEntities(std::vector<std::shared_ptr<Entity>, std::allocator<std::shared_ptr<Entity>>>*);
    virtual void
    removeEntities(std::vector<std::shared_ptr<Entity>, std::allocator<std::shared_ptr<Entity>>>*);
    virtual void disconnect(bool);
    virtual void mayInteract(std::shared_ptr<Player>, BlockPos const&, Block*);
    virtual void broadcastEntityEvent(std::shared_ptr<Entity>, unsigned int, int);
    virtual void blockEvent(BlockPos const&, Block*, int, int);
    virtual void updateSleepingPlayerList();
    virtual void createFireworks(double, double, double, double, double, double, CompoundTag*);
    virtual void pure_virtual_4() = 0;
    virtual void updateNeighbourForOutputSignal(BlockPos const&, Block*);
    virtual void sendPacketToServer(std::shared_ptr<Packet>);
    virtual void findNearestMapFeature(
        std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t>> const&,
        BlockPos const&, bool);
    virtual void newPrimedTntAllowed();
    virtual void newFallingBlockAllowed();
    virtual void explodeNextEnderCrystal();
    virtual void AllPlayersAreSleeping();

    bool isOutsideBuildHeight(BlockPos const&);
    LevelChunk* getChunkAt(BlockPos const&);
    LevelChunk* getChunk(int, int);

    BlockPos getTopSolidBlockPos(BlockPos const&);
    BlockPos getTopRainBlockPos(BlockPos const&);
    BlockPos getHeightmapPos(BlockPos const&);

    LevelData* getLevelData();
    WorldBorder* getWorldBorder();
    GameRules* getGameRules();
    Difficulty* getDifficulty();

    long long getSeed();
    int getSeaLevel();
    void setSeaLevel(int);
    static void enableLightingCache();

    long getGameTime();

    bool isRaining();
    bool isRainingAt(BlockPos const&);
    bool isHumidAt(BlockPos const&);

    void instaTick(BlockPos const&, BlockState const*, Random&);
    static void setInstaTick(bool);

    void addParticle(ParticleType const*, double, double, double, double, double, double,
                     arrayWithLength<int>);

    void blockEntityChanged(BlockPos const&, std::shared_ptr<BlockEntity>);
    void checkSession();  // RETURN TYPE UNKNOWN
    int dword8;
    char gapC[36];
    void* qword30;
    void* qword38;
    void* qword40;
    void* qword48;
    void* qword50;
    void* qword58;
    char gap60[40];
    void* qword88;
    void* qword90;
    void* qword98;
    void* qwordA0;
    void* qwordA8;
    void* qwordB0;
    void* qwordB8;
    void* qwordC0;
    void* qwordC8;
    void* qwordD0;
    void* qwordD8;
    void* qwordE0;
    void* qwordE8;
    void* qwordF0;
    void* qwordF8;
    void* qword100;
    void* qword108;
    void* qword110;
    void* qword118;
    void* qword120;
    void* qword128;
    void* qword130;
    int dword138;
    int dword13C;
    void* qword140;
    int dword148;
    int dword14C;
    void* qword150;
    void* qword158;
    void* qword160;
    void* qword168;
    Random* mRandom;
    void* qword178;
    Dimension* mDimension;
    char gap188[8];
    void* qword190;
    void* qword198;
    void* qword1A0;
    char gap1A8[8];
    void* qword1B0;
    void* qword1B8;
    void* qword1C0;
    char gap1C8[16];
    void* qword1D8;
    void* qword1E0;
    bool mIsLocal;
    char gap1E9[47];
    void* qword218;
    char gap220[32];
    void* qword240;
    void* qword248;
    void* qword250;
    char gap258[8];
    void* qword260;
    void* qword268;
    void* qword270;
};
