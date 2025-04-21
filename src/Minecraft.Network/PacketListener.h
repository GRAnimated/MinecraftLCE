#pragma once

#include "Minecraft.Network/protocol/game/DisconnectPacket.h"
#include <memory>

class Packet;

#define HANDLE(handlerName, packetType) virtual void handle##handlerName(std::shared_ptr<class packetType>)
#define HANDLE_IMPL(handlerName, packetType)                                                                 \
    void PacketListener::handle##handlerName(std::shared_ptr<packetType> packet) {                           \
        onUnhandledPacket(std::static_pointer_cast<Packet>(packet));                                         \
    }

class PacketListener {
public:
    PacketListener();
    virtual ~PacketListener();
    virtual void onUnhandledPacket(std::shared_ptr<Packet>);
    virtual void onDisconnect(DisconnectPacket::eDisconnectReason, void*);
    virtual void canHandleAsyncPackets();

    HANDLE(AcceptedLogin, ClientboundLoginPacket);
    HANDLE(GetInfo, GetInfoPacket);
    HANDLE(AddEntity, ClientboundAddEntityPacket);
    HANDLE(AddExperienceOrb, ClientboundAddExperienceOrbPacket);
    HANDLE(AddGlobalEntity, ClientboundAddGlobalEntityPacket);
    HANDLE(AddMob, ClientboundAddMobPacket);
    HANDLE(AddPainting, ClientboundAddPaintingPacket);
    HANDLE(AddPlayer, ClientboundAddPlayerPacket);
    HANDLE(Animate, ClientboundAnimatePacket);
    HANDLE(AwardStat, ClientboundAwardStatPacket);
    HANDLE(BlockDestruction, ClientboundBlockDestructionPacket);
    HANDLE(BlockCollectionDestruction, ClientboundBlockCollectionDestructionPacket);
    HANDLE(OpenSignEditor, ClientboundOpenSignEditorPacket);
    HANDLE(BlockEntityData, ClientboundBlockEntityDataPacket);
    HANDLE(BlockEvent, ClientboundBlockEventPacket);
    HANDLE(BlockUpdate, ClientboundBlockUpdatePacket);
    HANDLE(BlockRegionUpdate, BlockRegionUpdatePacket);
    HANDLE(Chat, ClientboundChatPacket);
    HANDLE(ChatAutoComplete, ClientboundChatAutoCompletePacket);
    HANDLE(ChunkBlocksUpdate, ClientboundChunkBlocksUpdatePacket);
    HANDLE(ChunkVisibility, ChunkVisibilityPacket);
    HANDLE(ChunkVisibilityArea, ChunkVisibilityAreaPacket);
    HANDLE(MapItemData, ClientboundMapItemDataPacket);
    HANDLE(ContainerAck, ClientboundContainerAckPacket);
    HANDLE(ContainerClose, ClientboundContainerClosePacket);
    HANDLE(ContainerContent, ClientboundContainerSetContentPacket);
    HANDLE(ContainerOpen, ClientboundContainerOpenPacket);
    HANDLE(ContainerSetData, ClientboundContainerSetDataPacket);
    HANDLE(ContainerSetSlot, ClientboundContainerSetSlotPacket);
    HANDLE(CustomPayload, ClientboundCustomPayloadPacket);
    HANDLE(Disconnect, DisconnectPacket);
    HANDLE(EntityActionAtPosition, ClientboundPlayerSleepPacket);
    HANDLE(EntityEvent, ClientboundEntityEventPacket);
    HANDLE(EntityLinkPacket, ClientboundSetEntityLinkPacket);
    HANDLE(SetEntityPassengersPacket, ClientboundSetPassengersPacket);
    HANDLE(Explosion, ClientboundExplodePacket);
    HANDLE(GameEvent, ClientboundGameEventPacket);
    HANDLE(KeepAlive, ClientboundKeepAlivePacket);
    HANDLE(LevelEvent, ClientboundLevelEventPacket);
    HANDLE(Login, ClientboundLoginPacket);
    HANDLE(MoveEntity, ClientboundMoveEntityPacket);
    HANDLE(MoveEntitySmall, MoveEntityPacketSmall);
    HANDLE(MovePlayer, ClientboundPlayerPositionPacket);
    HANDLE(ParticleEvent, ClientboundLevelParticlesPacket);
    HANDLE(PlayerAbilities, ClientboundPlayerAbilitiesPacket);
    HANDLE(PlayerInfo, PlayerInfoPacket);
    HANDLE(PreLogin, ClientboundPreLoginPacket);
    HANDLE(RemoveEntity, ClientboundRemoveEntitiesPacket);
    HANDLE(RemoveMobEffect, ClientboundRemoveMobEffectPacket);
    HANDLE(Respawn, ClientboundRespawnPacket);
    HANDLE(RotateMob, ClientboundRotateHeadPacket);
    HANDLE(SetCarriedItem, ClientboundSetCarriedItemPacket);
    HANDLE(SetEntityData, ClientboundSetEntityDataPacket);
    HANDLE(SetEntityMotion, ClientboundSetEntityMotionPacket);
    HANDLE(SetEquippedItem, ClientboundSetEquippedItemPacket);
    HANDLE(SetExperience, ClientboundSetExperiencePacket);
    HANDLE(SetHealth, ClientboundSetHealthPacket);
    HANDLE(SetPlayerTeamPacket, ClientboundSetPlayerTeamPacket);
    HANDLE(SetSpawn, ClientboundSetSpawnPositionPacket);
    HANDLE(SetTime, ClientboundSetTimePacket);
    HANDLE(SoundEvent, ClientboundSoundPacket);
    HANDLE(TakeItemEntity, ClientboundTakeItemEntityPacket);
    HANDLE(TeleportEntity, ClientboundTeleportEntityPacket);
    HANDLE(UpdateAttributes, ClientboundUpdateAttributesPacket);
    HANDLE(UpdateMobEffect, ClientboundUpdateMobEffectPacket);
    HANDLE(PlayerCombat, ClientboundPlayerCombatPacket);
    HANDLE(ChangeDifficulty, ClientboundChangeDifficultyPacket);
    HANDLE(SetCamera, ClientboundSetCameraPacket);
    HANDLE(SetBorder, ClientboundSetBorderPacket);
    HANDLE(SetTitles, ClientboundSetTitlesPacket);
    HANDLE(TabListCustomisation, ClientboundTabListPacket);
    HANDLE(ResourcePack, ClientboundResourcePackPacket);
    HANDLE(BossUpdate, ClientboundBossEventPacket);
    HANDLE(ItemCooldown, ClientboundCooldownPacket);
    HANDLE(MoveVehicle, ClientboundMoveVehiclePacket);
    HANDLE(ServerSettingsChanged, ServerSettingsChangedPacket);
    HANDLE(Texture, TexturePacket);
    HANDLE(TextureAndGeometry, TextureAndGeometryPacket);
    HANDLE(UpdateProgress, UpdateProgressPacket);
    HANDLE(TextureChange, TextureChangePacket);
    HANDLE(TextureAndGeometryChange, TextureAndGeometryChangePacket);
    HANDLE(UpdateGameRuleProgressPacket, UpdateGameRuleProgressPacket);
    HANDLE(XZ, XZPacket);
    HANDLE(ScoreboardPacket, ScoreboardPacket);
    HANDLE(GameMode, GameModePacket);
    HANDLE(MapSelectInfo, MapSelectInfoPacket);
    HANDLE(PlayerReady, PlayerReadyPacket);
    HANDLE(Powerup, ClientboundPowerupPacket);
    HANDLE(DamageIndicator, ClientboundDamageIndicatorPacket);
    HANDLE(MiniGamePlayerSettingsUpdatePacket, ClientboundMGPlayerSettingsUpdatePacket);
    HANDLE(Animate, ServerboundSwingPacket);
    HANDLE(Chat, ServerboundChatPacket);
    HANDLE(ChatAutoComplete, ServerboundChatAutoCompletePacket);
    HANDLE(ClientCommand, ServerboundClientCommandPacket);
    HANDLE(ClientInformation, ServerboundClientInformationPacket);
    HANDLE(ContainerAck, ServerboundContainerAckPacket);
    HANDLE(ContainerButtonClick, ServerboundContainerButtonClickPacket);
    HANDLE(ContainerClick, ServerboundContainerClickPacket);
    HANDLE(ContainerClose, ServerboundContainerClosePacket);
    HANDLE(CustomPayload, ServerboundCustomPayloadPacket);
    HANDLE(Interact, ServerboundInteractPacket);
    HANDLE(KeepAlive, ServerboundKeepAlivePacket);
    HANDLE(MovePlayer, ServerboundMovePlayerPacket);
    HANDLE(PlayerAbilities, ServerboundPlayerAbilitiesPacket);
    HANDLE(PlayerAction, ServerboundPlayerActionPacket);
    HANDLE(PlayerCommand, ServerboundPlayerCommandPacket);
    HANDLE(PlayerInput, ServerboundPlayerInputPacket);
    HANDLE(PreLogin, ServerboundPreLoginPacket);
    HANDLE(SetCarriedItem, ServerboundSetCarriedItemPacket);
    HANDLE(SetCreativeModeSlot, ServerboundSetCreativeModeSlotPacket);
    HANDLE(SignUpdate, ServerboundSignUpdatePacket);
    HANDLE(UseItemOn, ServerboundUseItemOnPacket);
    HANDLE(UseItem, ServerboundUseItemPacket);
    HANDLE(TeleportToEntityPacket, ServerboundTeleportToEntityPacket);
    HANDLE(ResourcePackResponse, ServerboundResourcePackPacket);
    HANDLE(PaddleBoat, ServerboundPaddleBoatPacket);
    HANDLE(MoveVehicle, ServerboundMoveVehiclePacket);
    HANDLE(AcceptTeleportPacket, ServerboundAcceptTeleportationPacket);
    HANDLE(CraftItem, CraftItemPacket);
    HANDLE(TradeItem, TradeItemPacket);
    HANDLE(DebugOptions, DebugOptionsPacket);
    HANDLE(KickPlayer, KickPlayerPacket);
    HANDLE(GameCommand, GameCommandPacket);
    HANDLE(Vote, VotePacket);
    HANDLE(ClientboundSetPlayerTeamPacket, ClientboundSetPlayerTeamPacket);

    virtual bool isServerPacketListener();
};
