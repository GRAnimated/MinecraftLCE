#pragma once

#include "types.h"
#include "Minecraft.World/ArrayWithLength.h"
#include "Minecraft.World/PlayerUID.h"
#include "Minecraft.World/eINSTANCEOF.h"
#include "Minecraft.World/entity/Entity.h"
#include "Minecraft.World/entity/LivingEntity.h"
#include "Minecraft.World/entity/player/Abilities.h"
#include "Minecraft.World/entity/player/FoodData.h"
#include "Minecraft.World/entity/player/StatsUID.h"
#include "Minecraft.World/item/ItemInstance.h"
#include "Minecraft.World/level/gamemode/minigames/glide/PowerupItems.h"
#include "Minecraft.World/sounds/SoundSource.h"
#include <cstdint>
#include <memory>
#include <string>

class DamageSource;
class Merchant;
class ItemEntity;
class CameraController;
class SignBlockEntity;
class BaseCommandBlock;
class CommandBlockEntity;
class Container;
class Stat;
class InteractionObject;
class AbstractHorse;
class Achievement;
class GameType;
class Inventory;
class PlayerEnderChestContainer;

class Player : public LivingEntity {
public:
    enum EPlayerGamePrivileges {

    };
    Player(Level*, std::wstring const&);
    static void staticCtor();

    virtual eINSTANCEOF GetType() override;
    virtual void defineSynchedData() override;
    virtual void resetPos() override;
    virtual void remove() override;
    virtual void tick() override;
    virtual int getPortalWaitTime() override;
    virtual void getSwimSound() override;
    virtual void getSwimSplashSound() override;
    virtual void playSound(SoundEvent const*, float, float) override;
    virtual bool makeStepSound() override;
    virtual void causeFallDamage(float, float) override;
    virtual void doWaterSplashEffect() override;
    virtual void push(std::shared_ptr<Entity>) override;
    virtual void hurt(DamageSource*, float) override;
    virtual bool isPickable() override;
    virtual void shouldRenderAtSqrDistance(double) override;
    virtual void readAdditionalSaveData(CompoundTag*) override;
    virtual void addAdditonalSaveData(CompoundTag*) override;
    virtual bool isInWall() override;
    virtual void rideTick() override;
    virtual void getRidingHeight() override;
    virtual void stopRiding() override;
    virtual void getDimensionChangingDelay() override;
    virtual void handleEntityEvent(unsigned char, int) override;
    virtual void getHandSlots() override;
    virtual void getArmorSlots() override;
    virtual void setItemSlot(EquipmentSlot const*, not_null_ptr<ItemInstance>) override;
    virtual bool isInvisibleTo(std::shared_ptr<Player>) override;
    virtual void getTeam() override;
    virtual void setInvisible(bool) override;
    virtual void ShouldRenderShadow() override;
    virtual void killed(std::shared_ptr<LivingEntity>) override;
    virtual void makeStuckInWeb() override;
    virtual void getName() override;
    virtual bool isPushedByWater() override;
    virtual std::wstring getDisplayName() override;
    virtual void shouldShowName() override;
    virtual void onSyncedDataUpdated(EntityDataAccessor_Base const*) override;
    virtual void getEyeHeight() override;
    virtual void setSlot(int, not_null_ptr<ItemInstance> const&) override;
    virtual SoundSource::ESoundSource getSoundSource() override;
    virtual void canCreateParticles() override;
    virtual void PositionLocked_4() override;
    virtual void SetPositionLocked_4(bool) override;
    virtual void TakeGlideCollisionDamage_4() override;
    virtual void SetGlideCollisionDamage_4(bool) override;
    virtual void GetLiftForceModifier_4() override;
    virtual void SetLiftForceModifier_4(double) override;
    virtual void registerAttributes() override;
    virtual void onChangedBlock(BlockPos const&) override;
    virtual void getExperienceReward(std::shared_ptr<Player>) override;
    virtual bool isAlwaysExperienceDropper() override;
    virtual void blockUsingShield(std::shared_ptr<LivingEntity> const&) override;
    virtual void die(DamageSource*) override;
    virtual void getHurtSound(DamageSource*) override;
    virtual void getDeathSound() override;
    virtual void getFallDamageSound(int) override;
    virtual void hurtArmor(float) override;
    virtual void hurtCurrentlyUsedShield(float) override;
    virtual void actuallyHurt(DamageSource, float) override;
    virtual void getItemSlot(EquipmentSlot const*) override;
    virtual void getItemInHandIcon(not_null_ptr<ItemInstance>, int) override;
    virtual bool isImmobile() override;
    virtual void jumpFromGround() override;
    virtual void travel(float, float, float) override;
    virtual void getSpeed() override;
    virtual bool isSleeping() override;
    virtual void aiStep() override;
    virtual void serverAiStep() override;
    virtual void pushEntities() override;
    virtual void getAbsorptionAmount() override;
    virtual void setAbsorptionAmount(float) override;
    virtual void getMainArm() override;
    virtual bool IsCreativeFlying() override;
    virtual void updateFrameTick();
    virtual void closeContainer();
    virtual void touch(std::shared_ptr<Entity> entToTouch);
    virtual void getScore();
    virtual void setScore(int);
    virtual void increaseScore(int);
    virtual void drop(bool allItems);
    virtual void reallyDrop(std::shared_ptr<ItemEntity>);
    virtual int GetThirdPersonView(bool);
    virtual void SetThirdPersonView(int);
    virtual bool CanChangeThirdPersonView();
    virtual CameraController* GetCameraController();
    virtual void SetCameraController(CameraController*, bool);
    virtual bool canHarmPlayer(std::shared_ptr<Player>);
    virtual bool canHarmPlayer(std::wstring);
    virtual float getArmorCoverPercentage();
    virtual void openTextEdit(std::shared_ptr<SignBlockEntity>);
    virtual void openMinecartCommandBlock(std::shared_ptr<BaseCommandBlock>);
    virtual void openCommandBlock(std::shared_ptr<CommandBlockEntity>);
    virtual void openTrading(std::shared_ptr<Merchant>, std::wstring const&, int);
    virtual void openContainer(std::shared_ptr<Container>);
    virtual void openHorseInventory(std::shared_ptr<AbstractHorse>, std::shared_ptr<Container>);
    virtual void startBlockInteraction(InteractionObject&);
    virtual void openItemInstanceGui(not_null_ptr<ItemInstance>, InteractionHand::EInteractionHand);
    virtual void interactOn(std::shared_ptr<Entity>, InteractionHand::EInteractionHand);
    virtual void attack(std::shared_ptr<Entity>);
    virtual void disableShield(bool);
    virtual void crit(std::shared_ptr<Entity>);
    virtual void magicCrit(std::shared_ptr<Entity>);
    virtual void respawn();
    virtual bool isLocalPlayer();
    virtual void getGameProfile();
    virtual void startSleepInBed(BlockPos const&, bool);
    virtual void stopSleepInBed(bool, bool, bool);
    virtual void displayClientMessage(int, bool);
    virtual void getRespawnPosition();
    virtual bool isRespawnForced();
    virtual void setRespawnPosition(BlockPos*, bool);
    virtual void hasAchievement(Achievement*);
    virtual void awardStat(Stat*, arrayWithLength<unsigned char>);
    virtual void resetStat(Stat*);
    virtual void checkMovementStatistiscs(double, double, double);
    virtual void increaseXp(int);
    virtual void getEnchantmentSeed();
    virtual void onEnchantmentPerformed(int);
    virtual void giveExperienceLevels(int);
    virtual void mayBuild();
    virtual void mayUseItemAt(BlockPos const&, Direction const*, not_null_ptr<ItemInstance>);
    virtual void onUpdateAbilities();
    virtual void setGameMode(GameType const*);
    virtual void isSpectator() = 0;
    virtual void GetScoreboard();
    virtual void onCrafted(not_null_ptr<ItemInstance>);
    virtual void getTexture();
    virtual void setCustomSkin(unsigned int);
    virtual void setCustomCape(unsigned int);
    virtual void handleCollectItem(not_null_ptr<ItemInstance>);
    virtual void SetCamera(std::shared_ptr<Entity>);
    virtual void SpectatePlayerNext();
    virtual void SpectatePlayerPrev();
    virtual void StopSpectatingPlayer();
    virtual bool IsSpectatingOtherPlayer();
    virtual void pure_virtual_12() = 0;
    virtual void GetGameMode();
    virtual void AutoEquip(not_null_ptr<ItemInstance>, bool&);
    virtual void OnEquipArmor(not_null_ptr<ItemInstance>);
    virtual void OnTakeFromAnvil(not_null_ptr<ItemInstance>);

    void init();
    void updatePlayerSize();
    void SetPowerupTicks(PowerupItems::eGlide_Timed_Powerup_ID, int ticks);
    // this is gameHostOption for player
    void setBool7FC(bool);
    bool isAllowedToAttackPlayers();
    bool hasInvisiblePrivilege();
    bool getPlayerGamePrivilege(EPlayerGamePrivileges);

    // dunno the type
    static std::vector<void*> sSkins;

    std::shared_ptr<Inventory> mInventory = nullptr;
    PlayerEnderChestContainer* mEnderChestInventory = nullptr;
    void* qword5C8 = nullptr;
    void* mInventoryMenu;
    void* mContainerMenu;
    FoodData mFoodData;
    int align;
    int mJumpTriggerTime;
    float mOBob;
    float mBob;
    int dword600;
    int dword604;
    std::wstring mCustomSkinName;
    std::wstring mCustomCapeName;
    int dword638;
    double mXCloakO;
    double mYCloakO;
    double mZCloakO;
    double mXCloak;
    double mYCloak;
    double mZCloak;
    std::wstring mNetworkName;
    char mSleeping;
    BlockPos* respawnPosition;
    int mSleepTimer;
    int somethingrelatedtorespawn;
    void* qword6A0;
    int dword6A8;
    void* qword6B0;
    BlockPos* mRespawnPosition;
    bool mRespawnForced;
    void* qword6C8;
    int WALK_ONE_CM;
    int WALK_ON_WATER_ONE_CM;
    int WALK_UNDER_WATER_ONE_CM;
    int FALL_ONE_CM;
    int CLIMB_ONE_CM;
    int MINECART_ONE_CM;
    int BOAT_ONE_CM;
    int PIG_ONE_CM;
    Abilities mAbilities;
    int mExperienceLevel;
    int mTotalExperience;
    float mExperienceProgress;
    void* qword710 = nullptr;
    void* qword718 = nullptr;
    int mEnchantmentSeed;
    int mDefaultFlySpeed;
    void* qword728;
    int mLastLevelUpTime;
    int dword734;
    std::wstring mGameProfile;
    bool mReducedDebugInfo;
    not_null_ptr<ItemInstance> mLastItemInMainHand;
    NonNullList<not_null_ptr<ItemInstance>> mTempHandSlots;
    CameraController* mCameraController;
    bool byte790;
    char byte791;
    char byte792;
    PlayerUID playerUID1 = PlayerUID(0);
    PlayerUID playerUID2 = PlayerUID(0);
    StatsUID statsUID = StatsUID();
    int dword7F8;
    bool bool7FC;
    bool bool7FD;
    NonNullList<not_null_ptr<ItemInstance>> mTempArmorSlots;
    int dword820;
    unsigned int mSkinId;
    unsigned int mSkinCapeId;
    unsigned int dword82C;
    int dword830;
    bool bool834;
    void* qword838;
    bool bool840;
    int mGamePrivileges;
    void* qword848;
    uint16_t word850;
    std::shared_ptr<Entity> mCameraEntity;
    bool mPositionLocked;
    bool mGlideCollisionDamage;
    double mLiftForceModifier;
    void* qword878;
    int mCurrentMiniGameID;
    char byte884;
    int mGlidepowerUpTicks[3];
    char byte894;
    void* qword898;
    void* qword8A0;
    int dword8A8;
};