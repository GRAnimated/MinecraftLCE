#pragma once

#include "Minecraft.World/pathfinding/BlockPathTypes.h"
#include "types.h"
#include "Minecraft.Client/resources/ResourceLocation.h"
#include "Minecraft.World/ArrayWithLength.h"
#include "Minecraft.World/entity/Entity.h"
#include "Minecraft.World/entity/LivingEntity.h"
#include "Minecraft.World/entity/ai/control/GoalSelector.h"
#include <string>

class ItemEntity;
class DifficultyInstance;
class MobGroupData;
class LookControl;
class MoveControl;
class JumpControl;
class PathNavigation;
class Sensing;
class BodyController;
class CensoredString;

class Mob : public LivingEntity {
public:
    Mob(Level*);

    virtual void registerGoals();
    virtual void createNavigation(Level*);
    virtual void getPathfindingMalus(BlockPathTypes const*);
    virtual void setPathfindingMalus(BlockPathTypes const*, float);
    virtual void createBodyControl();
    virtual void getLookControl();
    virtual void getMoveControl();
    virtual void getJumpControl();
    virtual void getNavigation();
    virtual void getSensing();
    virtual void getTarget();
    virtual void setTarget(std::shared_ptr<LivingEntity>);
    virtual void canAttackType(eINSTANCEOF);
    virtual void ate();
    virtual void getAmbientSoundInterval();
    virtual void playAmbientSound();
    virtual void resetAmbientSoundTime();
    virtual void spawnAnim();
    virtual void getAmbientSound();
    virtual void getDeathLoot();
    virtual void getDefaultLootTable();
    virtual void setZza(float);
    virtual void setYya(float);
    virtual void setXxa(float);
    virtual void pickUpItem(std::shared_ptr<ItemEntity>);
    virtual void canHoldItem(not_null_ptr<ItemInstance>);
    virtual void removeWhenFarAway();
    virtual void checkDespawn();
    virtual void customServerAiStep();
    virtual void getMaxHeadXRot();
    virtual void getMaxHeadYRot();
    virtual void checkSpawnRules();
    virtual void checkSpawnObstruction();
    virtual void getSizeScale();
    virtual void getHeadSizeScale();
    virtual void getMaxSpawnClusterSize();
    virtual void populateDefaultEquipmentSlots(const DifficultyInstance&);
    virtual void populateDefaultEquipmentEnchantments(const DifficultyInstance&);
    virtual void finalizeMobSpawn(const DifficultyInstance&, MobGroupData*, const std::wstring&);
    virtual void finalizeSpawnEggSpawn(int);
    virtual void canBeControlledByRider();
    virtual void setDropChance(EquipmentSlot const*, float);
    virtual void canPickUpLoot();
    virtual void setCanPickUpLoot(bool);
    virtual void isPersistenceRequired();
    virtual void mobInteract(std::shared_ptr<Player> const&, InteractionHand::EInteractionHand);
    virtual void tickLeash();
    virtual void dropLeash(bool, bool);
    virtual void canBeLeashed(std::shared_ptr<Player> const&);
    virtual void isLeashed();
    virtual void getLeashHolder();
    virtual void isLeashedToPlayer(std::shared_ptr<Player> const&);
    virtual void setLeashedTo(std::shared_ptr<Entity>, bool);
    virtual void restoreLeashFromSave();
    virtual void setNoAi(bool);
    virtual void setLeftHanded(bool);
    virtual void isNoAi();

    void init();

    int mAmbientSoundTime;
    int mXpReward;
    LookControl* mLookControl;
    MoveControl* mMoveControl;
    JumpControl* mJumpControl;
    BodyController* mBodyRotationControl;
    PathNavigation* mPathNavigation;
    GoalSelector mGoalSelector;
    GoalSelector mTargetSelector;
    std::shared_ptr<LivingEntity> mTarget;
    Sensing* mSensing;
    NonNullList<not_null_ptr<ItemInstance>> mHandItems;
    float mHandDropChances[2];
    NonNullList<not_null_ptr<ItemInstance>> mArmorItems;
    float mArmorDropChances[4];
    NonNullList<not_null_ptr<ItemInstance>> mNonNullListIdk;  // TODO: figure out where this is used
    arrayWithLength<float> mArrayOfFloats;                    // TODO: figure out where this is used
    bool mCanPickUpLoot;
    bool mPersistenceRequired;
    std::unordered_map<int, float>
        mPathfindingMalus;  // TODO: Key is BlockPathTypes but that requires hash or whatever
    std::shared_ptr<CensoredString> mCensoredString;
    bool mLeashed;
    std::shared_ptr<Entity> mLeashHolder;
    CompoundTag* mLeashInfoTag;
    float dword760;
    ResourceLocation* mLootTable;
    long mLootTableSeed;
};