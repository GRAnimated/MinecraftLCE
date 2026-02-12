#pragma once

#include "net/minecraft/world/InteractionHand.h"
#include "net/minecraft/world/level/gamemode/minigames/glide/GlideRingGenerator.h"
#include "types.h"
#include <memory>

class BlockPos;
class Direction;
class Player;
class Level;
class GameType;
class BlockItem;
class Item;
class Entity;
class CombatEntry;
class ClientboundChatPacket;
class ItemInstance;
class Minecraft;

class GameMode {
public:
    GameMode();
    virtual ~GameMode();
    virtual void startDestroyBlock(const BlockPos&, const Direction*) = 0;
    virtual void tick() = 0;
    virtual void useItem(std::shared_ptr<Player>, Level*, InteractionHand::EInteractionHand, bool) = 0;
    virtual void SetGameType(const GameType*) = 0;
    virtual void GetGameType() = 0;
    virtual bool CanRecordStatsAndAchievements();
    virtual void MayDestroy(const BlockPos&);
    virtual void MayPlace(const BlockPos&, BlockItem*);
    virtual void MayUse(const BlockPos&, Item*);
    virtual void GetMiniGame() = 0;
    virtual void GetPlayer() = 0;
    virtual void GetLevel() = 0;
    virtual void RecordDamage(std::shared_ptr<Entity>, CombatEntry*, std::shared_ptr<ClientboundChatPacket>);
    virtual void RecordDeath(std::shared_ptr<Entity>);
    virtual void RecordItem(not_null_ptr<ItemInstance>);
    virtual void RecordContainer(int, int, int, int);
    virtual void RecordWalk(int, bool, bool);
    virtual void RecordSwim(int, bool);
    virtual void RecordClimb(int);
    virtual void RecordUseItem(not_null_ptr<ItemInstance>);
    virtual void RecordJump();
    virtual void RecordGainPoints(int);
    virtual void ResetTempPoints();
    virtual bool RecordSecondaryTargetReached(const std::wstring&, int, GlideRingGenerator::eGlideRingSize);
    virtual bool RecordLastCheckpoint(int, int, bool, bool, bool);
    virtual bool RecordLapCompleted();
    virtual void RecordThermalEntered();
    virtual bool RecordProgress(double, double, double, double);
    virtual void RecordSpawnedAtCheckpoint(int);
    virtual void RecordBlockPlaced(const BlockPos&, int);
    virtual void RecordBlockDestroyed(const BlockPos&, int);
    virtual void RecordBlockPresent(const BlockPos&, int);
    virtual void RecordLayerTime();
    virtual void RecordSnowballHit();
    virtual void RecordHitBySnowball();
    virtual void RecordLanding(const BlockPos&);
    virtual void OnMouseDown();
    virtual void handleCraftItem(int, int, std::shared_ptr<Player>);
    virtual void handleStackedCraftItem(std::vector<std::pair<int, int>>&, int, std::shared_ptr<Player>);
    virtual void handleCustomCraftItem(std::vector<int>&, std::shared_ptr<Player>);

    bool isSpectator();
    bool isCreative();

private:
    Minecraft* m_minecraft;
    GameType* m_gameType;
};
