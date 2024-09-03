#pragma once

#include <memory>
#include "types.h"

class BlockPos;
class Direction;
class InteractionHand {
public:
    enum EInteractionHand {};
};
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
class GlideRingGenerator {
public:
    enum eGlideRingSize {};
};

class GameMode {
public:
    GameMode();
    virtual ~GameMode();
    virtual void startDestroyBlock(BlockPos const&, Direction const*) = 0;
    virtual void tick() = 0;
    virtual void useItem(std::shared_ptr<Player>, Level*, InteractionHand::EInteractionHand, bool) = 0;
    virtual void SetGameType(GameType const*) = 0;
    virtual void GetGameType() = 0;
    virtual bool CanRecordStatsAndAchievements();
    virtual void MayDestroy(BlockPos const&);
    virtual void MayPlace(BlockPos const&, BlockItem*);
    virtual void MayUse(BlockPos const&, Item*);
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
    virtual void* RecordSecondaryTargetReached(std::wstring const&, int, GlideRingGenerator::eGlideRingSize);
    virtual void RecordLastCheckpoint(int, int, bool, bool, bool);
    virtual void RecordLapCompleted();
    virtual void RecordThermalEntered();
    virtual void RecordProgress(double, double, double, double);
    virtual void RecordSpawnedAtCheckpoint(int);
    virtual void RecordBlockPlaced(BlockPos const&, int);
    virtual void RecordBlockDestroyed(BlockPos const&, int);
    virtual void RecordBlockPresent(BlockPos const&, int);
    virtual void RecordLayerTime();
    virtual void RecordSnowballHit();
    virtual void RecordHitBySnowball();
    virtual void RecordLanding(BlockPos const&);
    virtual void OnMouseDown();
    virtual void handleCraftItem(int, int, std::shared_ptr<Player>);
    virtual void handleStackedCraftItem(std::vector<std::pair<int, int>>&, int, std::shared_ptr<Player>);
    virtual void handleCustomCraftItem(std::vector<int>&, std::shared_ptr<Player>);

    bool isSpectator();

private:
    Minecraft* mMinecraft;
    GameType* mGameType;
};
