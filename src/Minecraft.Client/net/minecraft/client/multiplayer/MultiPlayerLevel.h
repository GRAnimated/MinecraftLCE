#pragma once

#include "net/minecraft/world/level/Level.h"
#include <unordered_set>

class ClientPacketListener;
class Minecart;
class Minecraft;
class ClientChunkCache;
class ClientScoreboard;

class MultiPlayerLevel : public Level {
public:
    struct ResetInfo {};

    MultiPlayerLevel(std::shared_ptr<LevelStorage>, ClientPacketListener*, LevelSettings*, int,
                     const Difficulty*);
    MultiPlayerLevel(ClientPacketListener*, LevelSettings*, int, const Difficulty*);

    ~MultiPlayerLevel() override;

    void MultiPlayerLevelInit(ClientPacketListener*, LevelSettings*, const Difficulty*);

    ChunkSource* createChunkSource() override;
    void validateSpawn() override;
    bool hasChunk(int, int, bool) override;
    bool setBlock(const BlockPos&, const BlockState*, int, bool) override;
    void playSound(std::shared_ptr<Player>, double, double, double, const SoundEvent*,
                   SoundSource::ESoundSource, float, float, float) override;
    void playLocalSound(double, double, double, const SoundEvent*, SoundSource::ESoundSource, float, float,
                        bool, float) override;
    bool addEntity(std::shared_ptr<Entity>) override;
    void entityAdded(std::shared_ptr<Entity>) override;
    void entityRemoved(std::shared_ptr<Entity>) override;
    void removeEntity(std::shared_ptr<Entity>) override;
    void tick() override;
    void tickWeather(bool) override;
    int getChunkPollRange() override;
    void tickClientSideBlocks(int, int, LevelChunk*) override;
    void tickBlocks() override;
    std::shared_ptr<Entity> getEntity(int) override;
    void removeEntities(std::vector<std::shared_ptr<Entity>>*) override;
    void disconnect(bool) override;
    void createFireworks(double, double, double, double, double, double, CompoundTag*) override;
    void sendPacketToServer(std::shared_ptr<Packet>) override;
    virtual void* makeSoundUpdater(std::shared_ptr<Minecart>);
    virtual void setDayTime(long long);

    ChunkSource* getChunkSource();
    void unshareChunkAt(int, int);
    void shareChunkAt(int, int);
    ClientScoreboard* GetClientScoreboard();

    std::vector<ResetInfo> field_2b0;
    bool byte_2c8;
    int dword_2cc;
    int dword_2d0;
    int dword_2d4;
    int dword_2d8;
    std::vector<ClientPacketListener*> mPacketListeners;
    ChunkSource* mCache;
    Minecraft* mMinecraft;
    ClientScoreboard* mClientScoreboard;
    std::unordered_map<EntityId, EntityPtr, IntKeyHash2, IntKeyEq, EntityIdMapAllocator> field_310;
    std::unordered_set<std::shared_ptr<Entity>> field_338;
    std::unordered_set<std::shared_ptr<Entity>> field_360;
    std::unordered_set<int> field_388;
    int field_3b0;
};
