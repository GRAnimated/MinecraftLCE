#pragma once

#include "net/minecraft/client/multiplayer/ServerGamePacketListenerImpl.h"
#include "net/minecraft/world/entity/Entity.h"
#include "net/minecraft/world/entity/player/Player.h"
#include "net/minecraft/world/inventory/ContainerListener.h"
#include <memory>

class ServerPlayer : public Player, net_minecraft_world_inventory::ContainerListener {
public:
    ~ServerPlayer() override;
    void sendMessage(ClientboundChatPacket::EChatPacketMessage, int*, uint, std::wstring*, uint) override;
    bool hasPermission(EGameCommand) override;
    bool isSendMessageEnabled() override;
    BlockPos getCommandSenderBlockPosition() override;
    eINSTANCEOF GetType() override;
    void tick() override;
    void processDimensionDelay() override;
    void checkFallDamage(double, bool, Block*, const BlockPos&) override;
    void hurt(DamageSource*, float) override;
    void readAdditionalSaveData(CompoundTag*) override;
    void addAdditonalSaveData(CompoundTag*) override;
    void startRiding(std::shared_ptr<Entity>) override;
    void stopRiding() override;
    void stopRidingBeforeTeleport() override;
    bool isInvulnerableTo(DamageSource*) override;
    void changeDimension(int) override;
    void teleportTo(double, double, double) override;
    void broadcastToPlayer(std::shared_ptr<ServerPlayer>) override;
    bool isCreative() override;
    void updateInvisibilityStatus() override;
    void addEffect(MobEffectInstance*, const std::shared_ptr<Entity>&) override;
    void onEffectAdded(MobEffectInstance*) override;
    void onEffectUpdated(MobEffectInstance*, bool) override;
    void onEffectRemoved(MobEffectInstance*) override;
    void checkTotemDeathProtection(DamageSource*) override;
    void die(DamageSource*) override;
    void swing(InteractionHand::EInteractionHand) override;
    void take(std::shared_ptr<Entity>, int) override;
    void onEnterCombat() override;
    void onLeaveCombat() override;
    void completeUsingItem() override;
    void closeContainer() override;
    bool canHarmPlayer(std::shared_ptr<Player>) override;
    bool canHarmPlayer(std::wstring) override;
    void openTextEdit(std::shared_ptr<SignBlockEntity>) override;
    void openTrading(std::shared_ptr<Merchant>, const std::wstring&, int) override;
    void openContainer(std::shared_ptr<Container>) override;
    void openHorseInventory(std::shared_ptr<AbstractHorse>, std::shared_ptr<Container>) override;
    void startBlockInteraction(InteractionObject&) override;
    void openItemInstanceGui(not_null_ptr<ItemInstance>, InteractionHand::EInteractionHand) override;
    void attack(std::shared_ptr<Entity>) override;
    void crit(std::shared_ptr<Entity>) override;
    void magicCrit(std::shared_ptr<Entity>) override;
    void startSleepInBed(const BlockPos&, bool) override;
    void stopSleepInBed(bool, bool, bool) override;
    void displayClientMessage(int, bool) override;
    void awardStat(Stat*, arrayWithLength<unsigned char>) override;
    void resetStat(Stat*) override;
    void onEnchantmentPerformed(int) override;
    void giveExperienceLevels(int) override;
    void onUpdateAbilities() override;
    void setGameMode(const GameType*) override;
    bool isSpectator() override;
    void handleCollectItem(not_null_ptr<ItemInstance>) override;
    void SetCamera(std::shared_ptr<Entity>) override;
    GameMode* GetGameMode() override;
    void OnEquipArmor(not_null_ptr<ItemInstance>) override;
    // somehow put openFireworks here
    void refreshContainer(AbstractContainerMenu*, std::vector<not_null_ptr<ItemInstance>>*) override;
    void slotChanged(AbstractContainerMenu*, int, not_null_ptr<ItemInstance>) override;
    void setContainerData(AbstractContainerMenu*, int, int) override;
    void setAllContainerData(AbstractContainerMenu*, std::shared_ptr<Container>) override;
    virtual void restoreFrom(std::shared_ptr<Player>, bool);
    virtual void teleportTo(double, double, double, float, float);

    void startFallFlying();

    // void* fill;
    std::shared_ptr<ServerGamePacketListenerImpl> mConnection;
};
