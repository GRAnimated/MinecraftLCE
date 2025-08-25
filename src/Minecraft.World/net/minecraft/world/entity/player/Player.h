#pragma once

#include "net/minecraft/sounds/SoundSource.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/PlayerUID.h"
#include "net/minecraft/world/eINSTANCEOF.h"
#include "net/minecraft/world/entity/Entity.h"
#include "net/minecraft/world/entity/LivingEntity.h"
#include "net/minecraft/world/entity/player/Abilities.h"
#include "net/minecraft/world/entity/player/StatsUID.h"
#include "net/minecraft/world/food/FoodData.h"
#include "net/minecraft/world/item/ItemInstance.h"
#include "net/minecraft/world/level/gamemode/minigames/glide/PowerupItems.h"
#include "types.h"
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
class InventoryMenu;
class PlayerEnderChestContainer;
class GameMode;

class Player : public LivingEntity {
public:
    enum EPlayerGamePrivileges {

    };
    Player(Level*, const std::wstring&);
    static void staticCtor();

    eINSTANCEOF GetType() override;
    void defineSynchedData() override;
    void resetPos() override;
    void remove() override;
    void tick() override;
    int getPortalWaitTime() override;
    void getSwimSound() override;
    void getSwimSplashSound() override;
    void playSound(const SoundEvent*, float, float) override;
    bool makeStepSound() override;
    void causeFallDamage(float, float) override;
    void doWaterSplashEffect() override;
    void push(std::shared_ptr<Entity>) override;
    void hurt(DamageSource*, float) override;
    bool isPickable() override;
    void shouldRenderAtSqrDistance(double) override;
    void readAdditionalSaveData(CompoundTag*) override;
    void addAdditonalSaveData(CompoundTag*) override;
    bool isInWall() override;
    void rideTick() override;
    void getRidingHeight() override;
    void stopRiding() override;
    void getDimensionChangingDelay() override;
    void handleEntityEvent(unsigned char, int) override;
    void getHandSlots() override;
    void getArmorSlots() override;
    void setItemSlot(const EquipmentSlot*, not_null_ptr<ItemInstance>) override;
    bool isInvisibleTo(std::shared_ptr<Player>) override;
    Team* getTeam() override;
    void setInvisible(bool) override;
    void ShouldRenderShadow() override;
    void killed(std::shared_ptr<LivingEntity>) override;
    void makeStuckInWeb() override;
    std::wstring getName() override;
    bool isPushedByWater() override;
    std::wstring getDisplayName() override;
    void shouldShowName() override;
    void onSyncedDataUpdated(const EntityDataAccessor_Base*) override;
    float getEyeHeight() override;
    void setSlot(int, const not_null_ptr<ItemInstance>&) override;
    SoundSource::ESoundSource getSoundSource() override;
    void canCreateParticles() override;
    bool PositionLocked() override;
    void SetPositionLocked(bool) override;
    void TakeGlideCollisionDamage() override;
    void SetGlideCollisionDamage(bool) override;
    double GetLiftForceModifier() override;
    void SetLiftForceModifier(double) override;
    void registerAttributes() override;
    void onChangedBlock(const BlockPos&) override;
    void getExperienceReward(std::shared_ptr<Player>) override;
    bool isAlwaysExperienceDropper() override;
    void blockUsingShield(const std::shared_ptr<LivingEntity>&) override;
    void die(DamageSource*) override;
    void getHurtSound(DamageSource*) override;
    void getDeathSound() override;
    void getFallDamageSound(int) override;
    void hurtArmor(float) override;
    void hurtCurrentlyUsedShield(float) override;
    void actuallyHurt(DamageSource, float) override;
    not_null_ptr<ItemInstance> getItemSlot(const EquipmentSlot*) override;
    void getItemInHandIcon(not_null_ptr<ItemInstance>, int) override;
    bool isImmobile() override;
    void jumpFromGround() override;
    void travel(float, float, float) override;
    float getSpeed() override;
    bool isSleeping() override;
    void aiStep() override;
    void serverAiStep() override;
    void pushEntities() override;
    float getAbsorptionAmount() override;
    void setAbsorptionAmount(float) override;
    void getMainArm() override;
    bool IsCreativeFlying() override;
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
    virtual void openTrading(std::shared_ptr<Merchant>, const std::wstring&, int);
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
    virtual void startSleepInBed(const BlockPos&, bool);
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
    virtual bool mayUseItemAt(const BlockPos&, const Direction*, not_null_ptr<ItemInstance>);
    virtual void onUpdateAbilities();
    virtual void setGameMode(const GameType*);
    virtual bool isSpectator() = 0;
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
    virtual GameMode* GetGameMode();
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
    int getPlayerGamePrivilege(EPlayerGamePrivileges);
    bool CheckPowerup(PowerupItems::eGlide_Timed_Powerup_ID);
    std::shared_ptr<ItemEntity> drop(not_null_ptr<ItemInstance>, bool);
    bool canDestroy(const BlockState*);
    float getDestroySpeed(const BlockState*);
    const StatsUID getSUID();
    PlayerUID getPlayerUID() { return this->playerUID1; }  // guessed name

    static std::vector<unsigned int> sSkins;

    std::shared_ptr<Inventory> mInventory = nullptr;
    PlayerEnderChestContainer* mEnderChestInventory = nullptr;
    void* qword5C8 = nullptr;
    InventoryMenu* mInventoryMenu;
    void* mContainerMenu;
    FoodData mFoodData;
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
    int mSizeType;
    char byte884;
    int mGlidepowerUpTicks[3];
    char byte894;
    void* qword898;
    void* qword8A0;
    int dword8A8;
};
