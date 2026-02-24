#pragma once

#include "net/minecraft/world/PlayerUID.h"
#include "net/minecraft/world/eINSTANCEOF.h"
#include "net/minecraft/world/level/saveddata/SavedData.h"
#include "nn/os/os_MutexTypes.h"
#include "types.h"
#include <memory>
#include <unordered_map>
#include <vector>

#include "net/minecraft/sounds/SoundSource.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/CustomSet.h"
#include "net/minecraft/world/IntKey.h"
#include "net/minecraft/world/level/GameRules.h"
#include "net/minecraft/world/level/storage/LevelSource.h"
#include "net/minecraft/world/phys/AABB.h"

class TickNextTickData;
class LevelSettings;
class LevelListener;
class Difficulty;
class Player;
class SoundEvent;
class ChunkSource;
class LevelChunk;
class LevelStorage;
class LevelData;
class Dimension;
class Villages;
class BoundingBox;
class CompoundTag;
class Packet;
class Random;
class WorldBorder;
class ParticleType;
class PathNavigationListener;
class MinecraftServer;
class SavedDataStorage;

using EntityPtr = std::shared_ptr<Entity>;
using EntityId = int;
using EntityIdMapAllocator = std::allocator<std::pair<const EntityId, EntityPtr>>;

class Level : public LevelSource {
public:
    static const int HEIGHT_LIMIT = 256;

    Level(std::shared_ptr<LevelStorage>, LevelData*, Dimension*, bool);

    std::shared_ptr<BlockEntity> getBlockEntity(const BlockPos&) override;
    int getLightColor(const BlockPos&, int, int) override;
    int getBrightness(LightLayer::variety, const BlockPos&) override;
    float getBrightness(const BlockPos&, int) override;
    float getBrightness(const BlockPos&) override;
    const BlockState* getBlockState(const BlockPos&) override;
    int getBlockId(int, int, int) override;
    int getBlockData(int, int, int) override;
    Block* getBlock(const BlockPos&) override;
    bool isEmptyBlock(const BlockPos&) override;
    Biome* getBiome(const BlockPos&) override;
    BiomeSource* getBiomeSource() override;
    int getMaxBuildHeight() override;
    bool isAllEmpty() override;
    int getDirectSignal(const BlockPos&, const Direction*) override;
    LevelType* getGeneratorType() override;
    ~Level() override;
    virtual void postConstruct();
    virtual ChunkSource* createChunkSource() = 0;
    virtual void initializeLevel(LevelSettings*);
    virtual MinecraftServer* getServer();
    virtual void validateSpawn();
    virtual bool hasChunk(int, int, bool) = 0;
    virtual bool isChunkGeneratedAt(int, int);
    virtual bool setBlock(const BlockPos&, const BlockState*, int, bool);
    virtual void setData(const BlockPos&, int, int, bool);
    virtual void setData(int, int, int, int, int, bool);
    virtual void removeBlock(const BlockPos&);
    virtual void destroyBlock(const BlockPos&, bool);
    virtual void setBlockAndUpdate(const BlockPos&, const BlockState*);
    virtual void sendBlockUpdated(const BlockPos&, const BlockState*, const BlockState*, int, bool);
    virtual bool isBlockToBeTickedAt(const BlockPos&, Block*);
    virtual void getNeighbourBrightnesses(int*, LightLayer::variety, int, int, int);
    virtual void playSound(std::shared_ptr<Player>, const BlockPos&, const SoundEvent*,
                           SoundSource::ESoundSource, float, float, float);
    virtual void playSound(std::shared_ptr<Player>, double, double, double, const SoundEvent*,
                           SoundSource::ESoundSource, float, float, float);
    virtual void playLocalSound(double, double, double, const SoundEvent*, SoundSource::ESoundSource, float,
                                float, bool, float);
    virtual bool addGlobalEntity(std::shared_ptr<Entity>);
    virtual bool addEntity(std::shared_ptr<Entity>);
    virtual void entityAdded(std::shared_ptr<Entity>);
    virtual void entityRemoved(std::shared_ptr<Entity>);
    virtual void playerRemoved(std::shared_ptr<Entity>);
    virtual void removeEntity(std::shared_ptr<Entity>);
    virtual bool hasTickNextTick(const BlockPos&, Block*);
    virtual void addToTickNextTick(const BlockPos&, Block*, int);
    virtual void addToTickNextTick(const BlockPos&, Block*, int, int);
    virtual void forceAddBlockTick(const BlockPos&, Block*, int, int);
    virtual void tickEntities();
    virtual void tickServerPlayers();
    virtual void tick(std::shared_ptr<Entity>, bool);
    virtual void explode(std::shared_ptr<Entity>, double, double, double, float, bool, bool, bool, bool, bool,
                         float);
    virtual void tick();
    virtual void blockEntityAddedExtra(std::shared_ptr<BlockEntity>);
    virtual void blockEntityRemovedExtra(std::shared_ptr<BlockEntity>);
    virtual void tickWeather(bool);
    virtual void buildAndPrepareChunksToPoll();
    virtual int getChunkPollRange() = 0;
    virtual void tickClientSideBlocks(int, int, LevelChunk*);
    virtual void tickBlocks();
    virtual bool tickPendingTicks(bool);
    virtual std::vector<TickNextTickData*>* fetchTicksInChunk(LevelChunk*, bool);
    virtual std::vector<TickNextTickData*>* fetchTicksInArea(BoundingBox*, bool);
    virtual std::shared_ptr<Entity> getEntity(int);
    virtual void addEntities(std::vector<std::shared_ptr<Entity>>*);
    virtual void removeEntities(std::vector<std::shared_ptr<Entity>>*);
    virtual void disconnect(bool);
    virtual bool mayInteract(std::shared_ptr<Player>, const BlockPos&, Block*);
    virtual void broadcastEntityEvent(std::shared_ptr<Entity>, unsigned int, int);
    virtual void blockEvent(const BlockPos&, Block*, int, int);
    virtual void updateSleepingPlayerList();
    virtual void createFireworks(double, double, double, double, double, double, CompoundTag*);
    virtual void GetScoreboard() = 0;
    virtual void updateNeighbourForOutputSignal(const BlockPos&, Block*);
    virtual void sendPacketToServer(std::shared_ptr<Packet>);
    virtual void* findNearestMapFeature(const std::wstring&, const BlockPos&, bool);
    virtual bool newPrimedTntAllowed();
    virtual bool newFallingBlockAllowed();
    virtual bool explodeNextEnderCrystal();
    virtual bool AllPlayersAreSleeping();

    void _init();
    bool hasChunkAt(const BlockPos&, bool);
    bool hasChunkAt(const BlockPos&, const BlockPos&);
    bool isOutsideBuildHeight(const BlockPos&);
    LevelChunk* getChunkAt(const BlockPos&);
    LevelChunk* getChunk(int, int);
    BlockPos getTopSolidBlockPos(const BlockPos&);
    BlockPos getTopRainBlockPos(const BlockPos&);
    BlockPos getHeightmapPos(const BlockPos&);
    BlockPos getSharedSpawnPos();
    LevelData* getLevelData();
    WorldBorder* getWorldBorder();
    GameRules* getGameRules();
    const Difficulty* getDifficulty();
    ChunkSource* getChunkSource();
    long long getSeed();
    int getSeaLevel();
    void setSeaLevel(int);
    static void enableLightingCache();
    void setSpawnPos(const BlockPos&);
    const BlockState* getTopBlockState(const BlockPos&);
    bool isInWorldBounds(const BlockPos&);
    bool isInWorldBounds(int, int, int);
    float getRainLevel(float);
    void blockUpdated(const BlockPos&, Block*, bool);
    void updateNeighborsAt(const BlockPos&, Block*, bool);
    void updateObservingBlocksAt(const BlockPos&, Block*);
    void observedNeighborChanged(const BlockPos&, Block*, const BlockPos&);
    void levelEvent(int, const BlockPos&, int);
    void levelEvent(std::shared_ptr<Player>, int, const BlockPos&, int);
    void lightColumnChanged(int, int, int, int);
    void checkLight(LightLayer::variety, const BlockPos&, bool, bool);
    void checkLight(const BlockPos&, bool, bool);
    void setBlocksDirty(const BlockPos&, const BlockPos&);
    void neighborChanged(const BlockPos&, Block*, const BlockPos&);
    bool canSeeSky(const BlockPos&);
    bool canSeeSkyFromBelowWater(const BlockPos&);
    int getRawBrightness(const BlockPos&);
    int getRawBrightness(const BlockPos&, bool);
    int getHeightmapHeight(int, int);
    int getHeightmap(int, int);
    bool isWithinLevelBounds(int, int);
    int getBrightnessPropagate(LightLayer::variety, const BlockPos&);
    long getGameTime();
    long getDayTime();
    bool isRaining();
    bool isRainingAt(const BlockPos&);
    bool isHumidAt(const BlockPos&);
    bool hasChunkAt(const BlockPos&);
    bool hasBlockCubes(const AABB*);
    void instaTick(const BlockPos&, const BlockState*, Random&);
    static void setInstaTick(bool);
    void addParticle(const ParticleType*, double, double, double, double, double, double,
                     arrayWithLength<int>);
    void blockEntityChanged(const BlockPos&, std::shared_ptr<BlockEntity>);
    void checkSession();  // RETURN TYPE UNKNOWN
    void addListener(LevelListener*);
    void removeListener(LevelListener*);
    int getHeight();
    int getFogDistance();
    int getSkyFlashTime();
    std::vector<AABB*>* getCollisionAABBs(std::shared_ptr<Entity>, const AABB*, bool, bool, bool);
    void updateSkyBrightness();
    void prepareWeather();
    void setDayTime(long long);
    bool hasChunksAt(const BlockPos&, const BlockPos&);
    int getAuxValueForMap(PlayerUID, int, int, int, int);
    std::shared_ptr<SavedData> getSavedData(const std::type_info&, const std::wstring&);
    void setSavedData(const std::wstring&, std::shared_ptr<SavedData>);
    std::vector<std::shared_ptr<Entity>>* getEntitiesOfClass(const std::type_info&, AABB const*);
    bool shouldFreezeIgnoreNeighbors(const BlockPos&);
    bool shouldSnow(const BlockPos&, bool);
    bool isFindingSpawn();
    unsigned int countInstanceOf(eINSTANCEOF, bool, unsigned int*, unsigned int*);

    int m_seaLevel = 63;
    nn::os::MutexType m_entityMutex;
    std::vector<std::shared_ptr<Entity>> m_entities;
    std::vector<std::shared_ptr<Entity>> m_entitiesToRemove;
    bool m_byte60;
    nn::os::MutexType m_blockEntityMutex;
    std::vector<std::shared_ptr<BlockEntity>> m_qword88;
    std::vector<std::shared_ptr<BlockEntity>> m_qwordA0;
    std::vector<std::shared_ptr<BlockEntity>> m_qwordB8;
    std::vector<std::shared_ptr<BlockEntity>> m_qwordD0;
    std::vector<std::shared_ptr<Player>> m_players;
    std::vector<std::shared_ptr<Entity>> m_globalEntities;
    std::unordered_map<EntityId, EntityPtr, IntKeyHash2, IntKeyEq, EntityIdMapAllocator> m_entityIdMap;
    int m_cloudColor;
    int m_skyDarken;
    bool m_byte148;
    int m_dword14c;
    void* m_qword150;
    int m_dword158;
    int m_dword15c;
    int m_dword160;
    int m_dword164;
    int m_dword168;
    int m_skyFlashTime;
    Random* m_random;
    bool m_byte178;
    Dimension* m_dimension;
    PathNavigationListener* m_pathNavigationListener;
    std::vector<LevelListener*> m_levelListeners;
    ChunkSource* m_chunkSource;
    std::shared_ptr<LevelStorage> m_levelStorage;
    LevelData* m_levelData;
    bool m_byte1c8;
    SavedDataStorage* m_savedDataStorage;
    std::shared_ptr<Villages> m_villages;
    bool m_isLocal;
    CustomSet m_chunksToPoll;
    bool m_byte210;
    bool m_byte211;
    bool m_byte212;
    WorldBorder* m_worldBorder;
    char m_gap220[32];
    std::vector<void*> m_qword240;
    void* m_qword258;
    std::vector<void*> m_qword260;
    ChunkSource* m_chunkCache;
    int m_xzSize;
    nn::os::MutexType m_unkMutex;
    int m_dword2a8;
    int m_fogDistance;
};

ASSERT_SIZEOF(Level, 0x2B0)
