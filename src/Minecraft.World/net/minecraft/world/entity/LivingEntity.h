#pragma once

#include "net/minecraft/core/NonNullList.h"
#include "net/minecraft/world/InteractionHand.h"
#include "net/minecraft/world/entity/Entity.h"
#include "net/minecraft/world/entity/MobType.h"
#include "net/minecraft/world/item/ItemInstance.h"
#include "net/minecraft/world/item/enchantment/Enchantment.h"
#include "net/minecraft/world/level/Level.h"
#include "types.h"
#include <cstdint>
#include <unordered_map>

class AttributeMap;
class Attribute;
class MobEffect;
class MobEffectInstance;
class CombatTracker;

class LivingEntity : public Entity {
public:
    LivingEntity(Level* level);

    int getUseItemRemainingTicks();

    eINSTANCEOF GetType() override;
    void fjDerivedCtorCalls() override;
    void kill() override;
    void defineSynchedData() override;
    void tick() override;
    void baseTick() override;
    void outOfWorld() override;
    void checkFallDamage(double, bool, Block*, const BlockPos&) override;
    void causeFallDamage(float, float) override;
    void getLightColor() override;
    void markHurt() override;
    void hurt(DamageSource*, float) override;
    Vec3* getViewVector(float) override;
    bool isPickable() override;
    bool isPushable() override;
    void readAdditionalSaveData(CompoundTag*) override;
    void addAdditonalSaveData(CompoundTag*) override;
    bool isAlive() override;
    void rideTick() override;
    void stopRiding() override;
    void lerpTo(double, double, double, float, float, int, bool) override;
    void handleEntityEvent(unsigned char, int) override;
    void animateHurt() override;
    void setSprinting(bool) override;
    void getTeam() override;
    void spawnEatParticles(const ItemInstance&, int) override;
    void getYHeadRot() override;
    void setYHeadRot(float) override;
    void setYBodyRot(float) override;
    void shouldShowName() override;
    void onSyncedDataUpdated(const EntityDataAccessor_Base*) override;
    void setBoundingBox(AABB* box) override;
    void stopCurrentLerp() override;
    virtual void registerAttributes();
    virtual bool isWaterMob();
    virtual void onChangedBlock(const BlockPos&);
    virtual bool isBaby();
    virtual void tickDeath();
    virtual void shouldDropExperience();
    virtual void decreaseAirSupply(int);
    virtual void getExperienceReward(std::shared_ptr<Player>);
    virtual bool isAlwaysExperienceDropper();
    virtual Random* getRandom();
    virtual void getLastHurtByMob();
    virtual void getLastHurtByMobTimestamp();
    virtual void setLastHurtByMob(std::shared_ptr<LivingEntity>);
    virtual void getLastHurtMob();
    virtual void getLastHurtMobTimestamp();
    virtual void setLastHurtMob(std::shared_ptr<Entity>);
    virtual void getNoActionTime();
    virtual void tickEffects();
    virtual void updateInvisibilityStatus();
    virtual void removeEffectParticles();
    virtual void removeAllEffects();
    virtual void getActiveEffects();
    virtual bool hasEffect(MobEffect*);
    virtual MobEffectInstance* getEffect(MobEffect*);
    virtual void addEffect(MobEffectInstance*, const std::shared_ptr<Entity>&);
    virtual void addEffectNoUpdate(MobEffectInstance*);
    virtual void canBeAffected(MobEffectInstance*);
    virtual bool isInvertedHealAndHarm();
    virtual void removeEffectNoUpdate(MobEffect*);
    virtual void removeEffect(MobEffect*);
    virtual void onEffectAdded(MobEffectInstance*);
    virtual void onEffectUpdated(MobEffectInstance*, bool);
    virtual void onEffectRemoved(MobEffectInstance*);
    virtual void heal(float);
    virtual void getHealth();
    virtual void setHealth(float);
    virtual void getLastDamageSource();
    virtual void blockUsingShield(const std::shared_ptr<LivingEntity>&);
    virtual void playHurtSound(DamageSource*);
    virtual void checkTotemDeathProtection(DamageSource*);
    virtual bool isDamageSourceBlocked(DamageSource*);
    virtual void breakItem(not_null_ptr<ItemInstance>);
    virtual void die(DamageSource*);
    virtual void dropEquipment(bool, int);
    virtual void knockback(std::shared_ptr<Entity>, float, double, double);
    virtual void getHurtSound(DamageSource*);
    virtual void getDeathSound();
    virtual void getFallDamageSound(int);
    virtual void dropAllDeathLoot(bool, int, DamageSource*);
    virtual void dropDeathLoot(bool, int);
    virtual bool onLadder();
    virtual bool isShootable();
    virtual void getArmorValue();
    virtual void hurtArmor(float);
    virtual void hurtCurrentlyUsedShield(float);
    virtual void getDamageAfterArmorAbsorb(DamageSource, float);
    virtual void getDamageAfterMagicAbsorb(DamageSource, float);
    virtual void actuallyHurt(DamageSource, float);
    virtual void getCombatTracker();
    virtual void getKillCredit();
    virtual void getMaxHealth();
    virtual void getArrowCount();
    virtual void setArrowCount(int);
    virtual void swing(InteractionHand::EInteractionHand);
    virtual void updateSwingTime();
    virtual Attribute* getAttribute(Attribute* attribute);
    virtual AttributeMap* getAttributes();
    virtual MobType getMobType();
    virtual void getMainHandItem();
    virtual void getOffhandItem();
    virtual not_null_ptr<ItemInstance> getItemInHand(InteractionHand::EInteractionHand);
    virtual void setItemInHand(InteractionHand::EInteractionHand, not_null_ptr<ItemInstance>);
    virtual bool hasItemInSlot(const EquipmentSlot*);
    virtual not_null_ptr<ItemInstance> getItemSlot(const EquipmentSlot*) = 0;
    virtual void getItemInHandIcon(not_null_ptr<ItemInstance>, int);
    virtual void getSoundVolume();
    virtual void getVoicePitch();
    virtual bool isImmobile();
    virtual void findStandUpPosition(std::shared_ptr<Entity>);
    virtual void getJumpPower();
    virtual void jumpFromGround();
    virtual void jumpInWater();
    virtual void jumpInLava();
    virtual float getWaterSlowDown();
    virtual void travel(float, float, float);
    virtual void updateModelAnimation();
    virtual float getSpeed();
    virtual void setSpeed(float);
    virtual void doHurtTarget(std::shared_ptr<Entity>);
    virtual bool isSleeping();
    virtual void tickHeadTurn(float, float);
    virtual void aiStep();
    virtual void serverAiStep();
    virtual void pushEntities();
    virtual void doPush(std::shared_ptr<Entity>);
    virtual void setJumping(bool);
    virtual void take(std::shared_ptr<Entity>, int);
    virtual bool canSee(std::shared_ptr<Entity>);
    virtual float getAttackAnim(float a2);
    virtual void getSweptVolume();
    virtual bool isEffectiveAi();
    virtual float getAbsorptionAmount();
    virtual void setAbsorptionAmount(float amount);
    virtual void onEnterCombat();
    virtual void onLeaveCombat();
    virtual void updateEffectVisibility();
    virtual void getMainArm() = 0;
    virtual bool isUsingItem();
    virtual void getUsedItemHand();
    virtual void updatingUsingItem();
    virtual void startUsingItem(InteractionHand::EInteractionHand);
    virtual void spawnItemUseParticles(not_null_ptr<ItemInstance>, int);
    virtual void completeUsingItem();
    virtual int getTicksUsingItem();
    virtual void releaseUsingItem();
    virtual void releaseUsingItem(int);
    virtual void stopUsingItem();
    virtual bool isBlocking();
    virtual bool isFallFlying();
    virtual void getFallFlyingTicks();
    virtual bool isAffectedByPotions();
    virtual void attackable();
    virtual void setRecordPlayingNearby(const BlockPos&, bool);
    virtual bool IsCreativeFlying();

    void init();
    void CheckThermalAreas();
    void fallFlyingTravel(double&, double&, double&, Vec3*, float&, float&, double&, double);
    not_null_ptr<ItemInstance> getUseItem();

    Attribute* mAttributes;
    CombatTracker* mCombatTracker;
    std::unordered_map<MobEffect*, MobEffectInstance*> mActivePotionsMap;
    NonNullList<not_null_ptr<ItemInstance>> mLastHandItemStacks;
    NonNullList<not_null_ptr<ItemInstance>> mLastArmorItemStacks;
    bool mSwinging;
    InteractionHand::EInteractionHand mSwingingArm;
    int mSwingTime;
    int mSwingTime2;
    int mRemoveArrowTime;
    int mHurtTime;
    int mHurtDuration;
    float mHurtDir;
    int mDeathTime;
    float mOAttackAnim;
    float mAttackAnim;
    int mAttackStrengthTicker;
    float mAnimationSpeedOld;
    float mAnimationSpeed;
    float mAnimationPosition;
    int dword36C;
    float mTilto;
    float mTilt;
    float mRandomUnused2;
    float mRandomUnused1;
    float mYBodyRot;
    float mYBodyRotO;
    float mYHeadRot;
    float mYHeadRot0;
    float mFlyingSpeed;
    double double398;
    double double3A0;
    char byte3A8;
    int dword3AC;
    void* qword3B0;
    char byte3B8;
    void* qword3C0;
    uint16_t word3C8;
    void* qword3D0;
    void* qword3D8;
    char gap3E0;
    char byte3E1;
    void* qword3E8;
    char byte3F0;
    int dword3F4;
    char gap3F8[24];
    char byte410;
    std::shared_ptr<Player> mLastHurtByPlayer;
    int mLastHurtByPlayerTime;
    int mIsDead;
    int mNoActionTime;
    float mORun;
    float mRun;
    float mAnimStep;
    float mOAnimStep;
    float mRotOffs;
    int mDeathScore;
    float mLastHurt;
    bool mJumping;
    float mXxa;
    float mYya;
    float mZza;
    float mYRotA;
    int mLerpSteps;
    double mLerpX;
    double mLerpY;
    double mLerpZ;
    double mLerpYRot;
    double mLerpXRot;
    bool mEffectsDirty;
    std::shared_ptr<LivingEntity> mLastHurtByMob;
    int mLastHurtByMobTimestamp;
    std::shared_ptr<LivingEntity> mLastHurtMob;
    int mLastHurtMobTimestamp;
    float mSpeed;
    int mNoJumpDelay;
    float mAbsorptionAmount;
    not_null_ptr<ItemInstance> mUseItem;
    int mUseItemRemaining;
    int mFallFlyTicks;
    BlockPos mLastPos;
    DamageSource* mLastDamageSource;
    long mLastDamageStamp;
    char byte508;
    int dword50C;
    int mMinX;
    int mMaxX;
    int mMinY;
    int mMaxY;
    int mMinZ;
    int mMaxZ;
    char gap528[128];
    char byte5A8;
    int dword5AC;
};
