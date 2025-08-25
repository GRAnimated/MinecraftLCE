#include "net/minecraft/network/protocol/Packet.h"

#import "game/BlockRegionUpdatePacket.h"
#import "game/ChunkVisibilityAreaPacket.h"
#import "game/ChunkVisibilityPacket.h"
#import "game/ClientboundAddEntityPacket.h"
#import "game/ClientboundAddExperienceOrbPacket.h"
#import "game/ClientboundAddGlobalEntityPacket.h"
#import "game/ClientboundAddMobPacket.h"
#import "game/ClientboundAddPaintingPacket.h"
#import "game/ClientboundAddPlayerPacket.h"
#import "game/ClientboundAnimatePacket.h"
#import "game/ClientboundAwardStatPacket.h"
#import "game/ClientboundBlockCollectionDestructionPacket.h"
#import "game/ClientboundBlockDestructionPacket.h"
#import "game/ClientboundBlockEntityDataPacket.h"
#import "game/ClientboundBlockEventPacket.h"
#import "game/ClientboundBlockUpdatePacket.h"
#import "game/ClientboundBossEventPacket.h"
#import "game/ClientboundChangeDifficultyPacket.h"
#import "game/ClientboundChatPacket.h"
#import "game/ClientboundChunkBlocksUpdatePacket.h"
#import "game/ClientboundContainerAckPacket.h"
#import "game/ClientboundContainerClosePacket.h"
#import "game/ClientboundContainerOpenPacket.h"
#import "game/ClientboundContainerSetContentPacket.h"
#import "game/ClientboundContainerSetDataPacket.h"
#import "game/ClientboundContainerSetSlotPacket.h"
#import "game/ClientboundCooldownPacket.h"
#import "game/ClientboundCustomPayloadPacket.h"
#import "game/ClientboundDamageIndicatorPacket.h"
#import "game/ClientboundEntityEventPacket.h"
#import "game/ClientboundExplodePacket.h"
#import "game/ClientboundGameEventPacket.h"
#import "game/ClientboundKeepAlivePacket.h"
#import "game/ClientboundLevelEventPacket.h"
#import "game/ClientboundLevelParticlesPacket.h"
#import "game/ClientboundLoginPacket.h"
#import "game/ClientboundMGPlayerSettingsUpdatePacket.h"
#import "game/ClientboundMapItemDataPacket.h"
#import "game/ClientboundMoveEntityPacket.h"
#import "game/ClientboundMoveVehiclePacket.h"
#import "game/ClientboundOpenSignEditorPacket.h"
#import "game/ClientboundPlayerAbilitiesPacket.h"
#import "game/ClientboundPlayerCombatPacket.h"
#import "game/ClientboundPlayerPositionPacket.h"
#import "game/ClientboundPlayerSleepPacket.h"
#import "game/ClientboundPowerupPacket.h"
#import "game/ClientboundPreLoginPacket.h"
#import "game/ClientboundRemoveEntitiesPacket.h"
#import "game/ClientboundRemoveMobEffectPacket.h"
#import "game/ClientboundResourcePackPacket.h"
#import "game/ClientboundRespawnPacket.h"
#import "game/ClientboundRotateHeadPacket.h"
#import "game/ClientboundSetBorderPacket.h"
#import "game/ClientboundSetCameraPacket.h"
#import "game/ClientboundSetCarriedItemPacket.h"
#import "game/ClientboundSetEntityDataPacket.h"
#import "game/ClientboundSetEntityLinkPacket.h"
#import "game/ClientboundSetEntityMotionPacket.h"
#import "game/ClientboundSetEquippedItemPacket.h"
#import "game/ClientboundSetExperiencePacket.h"
#import "game/ClientboundSetHealthPacket.h"
#import "game/ClientboundSetPassengersPacket.h"
#import "game/ClientboundSetPlayerTeamPacket.h"
#import "game/ClientboundSetSpawnPositionPacket.h"
#import "game/ClientboundSetTimePacket.h"
#import "game/ClientboundSetTitlesPacket.h"
#import "game/ClientboundSoundPacket.h"
#import "game/ClientboundTabListPacket.h"
#import "game/ClientboundTakeItemEntityPacket.h"
#import "game/ClientboundTeleportEntityPacket.h"
#import "game/ClientboundUpdateAttributesPacket.h"
#import "game/ClientboundUpdateMobEffectPacket.h"
#import "game/CraftItemPacket.h"
#import "game/DebugOptionsPacket.h"
#import "game/DisconnectPacket.h"
#import "game/GameCommandPacket.h"
#import "game/GameModePacket.h"
#import "game/GetInfoPacket.h"
#import "game/KickPlayerPacket.h"
#import "game/MapSelectInfoPacket.h"
#import "game/MoveEntityPacketSmall.h"
#import "game/PlayerInfoPacket.h"
#import "game/PlayerReadyPacket.h"
#import "game/ScoreboardPacket.h"
#import "game/ServerSettingsChangedPacket.h"
#import "game/ServerboundAcceptTeleportationPacket.h"
#import "game/ServerboundChatAutoCompletePacket.h"
#import "game/ServerboundChatPacket.h"
#import "game/ServerboundClientCommandPacket.h"
#import "game/ServerboundContainerAckPacket.h"
#import "game/ServerboundContainerButtonClickPacket.h"
#import "game/ServerboundContainerClickPacket.h"
#import "game/ServerboundContainerClosePacket.h"
#import "game/ServerboundCustomPayloadPacket.h"
#import "game/ServerboundInteractPacket.h"
#import "game/ServerboundKeepAlivePacket.h"
#import "game/ServerboundMovePlayerPacket.h"
#import "game/ServerboundMoveVehiclePacket.h"
#import "game/ServerboundPaddleBoatPacket.h"
#import "game/ServerboundPlayerAbilitiesPacket.h"
#import "game/ServerboundPlayerActionPacket.h"
#import "game/ServerboundPlayerCommandPacket.h"
#import "game/ServerboundPlayerInputPacket.h"
#import "game/ServerboundPreLoginPacket.h"
#import "game/ServerboundResourcePackPacket.h"
#import "game/ServerboundSetCarriedItemPacket.h"
#import "game/ServerboundSetCreativeModeSlotPacket.h"
#import "game/ServerboundSignUpdatePacket.h"
#import "game/ServerboundSwingPacket.h"
#import "game/ServerboundTeleportToEntityPacket.h"
#import "game/ServerboundUseItemOnPacket.h"
#import "game/ServerboundUseItemPacket.h"
#import "game/TextureAndGeometryChangePacket.h"
#import "game/TextureAndGeometryPacket.h"
#import "game/TextureChangePacket.h"
#import "game/TexturePacket.h"
#import "game/TradeItemPacket.h"
#import "game/UpdateGameRuleProgressPacket.h"
#import "game/UpdateProgressPacket.h"
#import "game/VotePacket.h"
#import "game/XZPacket.h"

#include "net/minecraft/core/System.h"

#include <sstream>

Packet::Packet() {
    mCreatedTime = System::processTimeInMilliSecs();
    mShouldDelay = false;
}

void Packet::handle(PacketListener* listener) {
    return;
}

int Packet::getEstimatedSize() {
    return 8;
}

bool Packet::canBeInvalidated() {
    return false;
}

bool Packet::isInvalidatedBy(std::shared_ptr<Packet> packet) {
    return false;
}

// amazing
bool Packet::isAync() {
    return false;
}

bool Packet::tryReplaceDuplicatePacket(std::deque<std::shared_ptr<Packet>>* duplicatePacket) {
    return false;
}

std::wstring Packet::readUtf(DataInputStream* in, int maxLength) {
    short length = in->readShort();

    if (length > maxLength) {
        std::wstringstream warning;
        warning << L"Received string length longer than maximum allowed (" << length << L" > " << maxLength
                << L")";
    }

    std::wstring str = L"";
    for (int i = 0; i < length; ++i) {
        str.push_back(in->readChar());
    }

    return str;
}

void Packet::map(int a1, bool a2, bool a3, bool a4, bool a5, const std::type_info& a6,
                 std::shared_ptr<Packet> (*a7)(), std::wstring a8) {
    map(a1, a2, a3, a4, a5, typeid(ClientboundKeepAlivePacket), a7, L"");
}

void Packet::staticCtor() {
    map(0, true, true, true, false, typeid(ClientboundKeepAlivePacket), ClientboundKeepAlivePacket::create,
        L"KeepAlive");
    map(1, true, true, true, false, typeid(ClientboundLoginPacket), ClientboundLoginPacket::create, L"Login");
    map(2, true, true, true, false, typeid(ClientboundPreLoginPacket), ClientboundPreLoginPacket::create,
        L"PreLogin");
    map(3, true, true, true, false, typeid(ClientboundChatPacket), ClientboundChatPacket::create, L"Chat");
    map(4, true, false, false, false, typeid(ClientboundSetTimePacket), ClientboundSetTimePacket::create,
        L"SetTime");
    map(5, true, false, false, false, typeid(ClientboundSetEquippedItemPacket),
        ClientboundSetEquippedItemPacket::create, L"SetEquippedItem");
    map(6, true, false, true, false, typeid(ClientboundSetSpawnPositionPacket),
        ClientboundSetSpawnPositionPacket::create, L"SetSpawnPosition");
    map(7, false, true, false, false, typeid(ServerboundInteractPacket), ServerboundInteractPacket::create,
        L"Interact");
    map(8, true, false, true, false, typeid(ClientboundSetHealthPacket), ClientboundSetHealthPacket::create,
        L"SetHealth");
    map(9, true, true, true, false, typeid(ClientboundRespawnPacket), ClientboundRespawnPacket::create,
        L"Respawn");
    map(10, true, true, true, false, typeid(ServerboundMovePlayerPacket), ServerboundMovePlayerPacket::create,
        L"MovePlayer");
    map(11, true, true, true, false, typeid(ServerboundMovePlayerPacket::Pos),
        ServerboundMovePlayerPacket::Pos::create, L"MovePlayer");
    map(12, true, true, true, false, typeid(ServerboundMovePlayerPacket::Rot),
        ServerboundMovePlayerPacket::Rot::create, L"MovePlayer");
    map(13, true, true, true, false, typeid(ServerboundMovePlayerPacket::PosRot),
        ServerboundMovePlayerPacket::PosRot::create, L"MovePlayer");
    map(14, false, true, false, false, typeid(ServerboundPlayerActionPacket),
        ServerboundPlayerActionPacket::create, L"PlayerAction");
    map(15, false, true, false, false, typeid(ServerboundUseItemPacket), ServerboundUseItemPacket::create,
        L"UseItem");
    map(16, true, true, true, false, typeid(ClientboundSetCarriedItemPacket),
        ClientboundSetCarriedItemPacket::create, L"SetCarriedItem");
    map(17, true, false, true, false, typeid(ClientboundPlayerSleepPacket),
        ClientboundPlayerSleepPacket::create, L"PlayerSleep");
    map(18, true, true, true, false, typeid(ClientboundAnimatePacket), ClientboundAnimatePacket::create,
        L"Animate");
    map(19, false, true, false, false, typeid(ServerboundPlayerCommandPacket),
        ServerboundPlayerCommandPacket::create, L"PlayerCommand");
    map(20, true, false, false, false, typeid(ClientboundAddPlayerPacket), ClientboundAddPlayerPacket::create,
        L"AddPlayer");
    map(22, true, false, true, false, typeid(ClientboundTakeItemEntityPacket),
        ClientboundTakeItemEntityPacket::create, L"TakeItemEntity");
    map(23, true, false, false, false, typeid(ClientboundAddEntityPacket), ClientboundAddEntityPacket::create,
        L"AddEntity");
    map(24, true, false, false, false, typeid(ClientboundAddMobPacket), ClientboundAddMobPacket::create,
        L"AddMob");
    map(25, true, false, false, false, typeid(ClientboundAddPaintingPacket),
        ClientboundAddPaintingPacket::create, L"AddPainting");
    map(26, true, false, false, false, typeid(ClientboundAddExperienceOrbPacket),
        ClientboundAddExperienceOrbPacket::create, L"AddExperienceOrb");
    map(27, false, true, false, false, typeid(ServerboundPlayerInputPacket),
        ServerboundPlayerInputPacket::create, L"PlayerInput");
    map(28, true, false, true, false, typeid(ClientboundSetEntityMotionPacket),
        ClientboundSetEntityMotionPacket::create, L"SetEntityMotion");
    map(29, true, false, false, false, typeid(ClientboundRemoveEntitiesPacket),
        ClientboundRemoveEntitiesPacket::create, L"RemoveEntities");
    map(30, true, false, false, false, typeid(ClientboundMoveEntityPacket),
        ClientboundMoveEntityPacket::create, L"MoveEntity");
    map(31, true, false, false, false, typeid(ClientboundMoveEntityPacket::Pos),
        ClientboundMoveEntityPacket::Pos::create, L"MoveEntity");
    map(32, true, false, false, false, typeid(ClientboundMoveEntityPacket::Rot),
        ClientboundMoveEntityPacket::Rot::create, L"MoveEntity");
    map(33, true, false, false, false, typeid(ClientboundMoveEntityPacket::PosRot),
        ClientboundMoveEntityPacket::PosRot::create, L"MoveEntity");
    map(34, true, false, false, false, typeid(ClientboundTeleportEntityPacket),
        ClientboundTeleportEntityPacket::create, L"TeleportEntity");
    map(35, true, false, false, false, typeid(ClientboundRotateHeadPacket),
        ClientboundRotateHeadPacket::create, L"RotateHead");
    map(38, true, false, true, false, typeid(ClientboundEntityEventPacket),
        ClientboundEntityEventPacket::create, L"EntityEvent");
    map(39, true, false, true, false, typeid(ClientboundSetEntityLinkPacket),
        ClientboundSetEntityLinkPacket::create, L"SetEntityLink");
    map(40, true, false, true, false, typeid(ClientboundSetEntityDataPacket),
        ClientboundSetEntityDataPacket::create, L"SetEntityData");
    map(41, true, false, true, false, typeid(ClientboundUpdateMobEffectPacket),
        ClientboundUpdateMobEffectPacket::create, L"UpdateMobEffect");
    map(42, true, false, true, false, typeid(ClientboundRemoveMobEffectPacket),
        ClientboundRemoveMobEffectPacket::create, L"RemoveMobEffect");
    map(43, true, false, true, false, typeid(ClientboundSetExperiencePacket),
        ClientboundSetExperiencePacket::create, L"SetExperience");
    map(44, true, false, true, false, typeid(ClientboundUpdateAttributesPacket),
        ClientboundUpdateAttributesPacket::create, L"UpdateAttributes");
    map(50, true, false, true, false, typeid(ChunkVisibilityPacket), ChunkVisibilityPacket::create,
        L"ChunkVisibility");
    map(51, true, false, true, false, typeid(BlockRegionUpdatePacket), BlockRegionUpdatePacket::create,
        L"BlockRegionUpdate");
    map(52, true, false, true, false, typeid(ClientboundChunkBlocksUpdatePacket),
        ClientboundChunkBlocksUpdatePacket::create, L"ChunkBlocksUpdate");
    map(53, true, false, true, false, typeid(ClientboundBlockUpdatePacket),
        ClientboundBlockUpdatePacket::create, L"BlockUpdate");
    map(54, true, false, true, false, typeid(ClientboundBlockEventPacket),
        ClientboundBlockEventPacket::create, L"BlockEvent");
    map(55, true, false, false, false, typeid(ClientboundBlockDestructionPacket),
        ClientboundBlockDestructionPacket::create, L"BlockDestruction");
    map(60, true, false, true, false, typeid(ClientboundExplodePacket), ClientboundExplodePacket::create,
        L"Explode");
    map(61, true, false, true, false, typeid(ClientboundLevelEventPacket),
        ClientboundLevelEventPacket::create, L"LevelEvent");
    map(62, true, true, true, false, typeid(ClientboundSoundPacket), ClientboundSoundPacket::create,
        L"Sound");
    map(63, true, false, true, false, typeid(ClientboundLevelParticlesPacket),
        ClientboundLevelParticlesPacket::create, L"LevelParticles");
    map(70, true, false, false, false, typeid(ClientboundGameEventPacket), ClientboundGameEventPacket::create,
        L"GameEvent");
    map(71, true, false, false, false, typeid(ClientboundAddGlobalEntityPacket),
        ClientboundAddGlobalEntityPacket::create, L"AddGlobalEntity");
    map(100, true, false, true, false, typeid(ClientboundContainerOpenPacket),
        ClientboundContainerOpenPacket::create, L"ContainerOpen");
    map(101, true, true, true, false, typeid(ClientboundContainerClosePacket),
        ClientboundContainerClosePacket::create, L"ContainerClose");
    map(102, false, true, false, false, typeid(ServerboundContainerClickPacket),
        ServerboundContainerClickPacket::create, L"ContainerClick");
    map(103, true, false, true, false, typeid(ClientboundContainerSetSlotPacket),
        ClientboundContainerSetSlotPacket::create, L"ContainerSetSlot");
    map(104, true, false, true, false, typeid(ClientboundContainerSetContentPacket),
        ClientboundContainerSetContentPacket::create, L"ContainerSetContent");
    map(105, true, false, true, false, typeid(ClientboundContainerSetDataPacket),
        ClientboundContainerSetDataPacket::create, L"ContainerSetData");
    map(106, true, true, true, false, typeid(ClientboundContainerAckPacket),
        ClientboundContainerAckPacket::create, L"ContainerAck");
    map(107, true, true, true, false, typeid(ServerboundSetCreativeModeSlotPacket),
        ServerboundSetCreativeModeSlotPacket::create, L"SetCreativeModeSlot");
    map(108, false, true, false, false, typeid(ServerboundContainerButtonClickPacket),
        ServerboundContainerButtonClickPacket::create, L"ContainerButtonClick");
    map(132, true, false, true, false, typeid(ClientboundBlockEntityDataPacket),
        ClientboundBlockEntityDataPacket::create, L"BlockEntityData");
    map(133, true, false, false, false, typeid(ClientboundMoveVehiclePacket),
        ClientboundMoveVehiclePacket::create, L"MoveVehicle");
    map(134, true, false, false, false, typeid(ClientboundSetPassengersPacket),
        ClientboundSetPassengersPacket::create, L"SetPassengers");
    map(135, false, true, false, false, typeid(ServerboundAcceptTeleportationPacket),
        ServerboundAcceptTeleportationPacket::create, L"AcceptTeleportation");
    map(136, false, true, false, false, typeid(ServerboundMoveVehiclePacket),
        ServerboundMoveVehiclePacket::create, L"MoveVehicle");
    map(137, false, true, false, false, typeid(ServerboundUseItemOnPacket),
        ServerboundUseItemOnPacket::create, L"UseItemOn");
    map(138, false, true, false, false, typeid(ServerboundPaddleBoatPacket),
        ServerboundPaddleBoatPacket::create, L"PaddleBoat");
    map(139, true, false, true, false, typeid(ClientboundBossEventPacket), ClientboundBossEventPacket::create,
        L"BossEvent");
    map(150, false, true, false, false, typeid(CraftItemPacket), CraftItemPacket::create, L"CraftItem");
    map(151, false, true, true, false, typeid(TradeItemPacket), TradeItemPacket::create, L"TradeItem");
    map(152, false, true, false, false, typeid(DebugOptionsPacket), DebugOptionsPacket::create,
        L"DebugOptions");
    map(153, true, true, false, false, typeid(ServerSettingsChangedPacket),
        ServerSettingsChangedPacket::create, L"ServerSettingsChanged");
    map(154, true, true, true, false, typeid(TexturePacket), TexturePacket::create, L"Texture");
    map(155, true, false, true, false, typeid(ChunkVisibilityAreaPacket), ChunkVisibilityAreaPacket::create,
        L"ChunkVisibilityArea");
    map(156, true, false, false, false, typeid(UpdateProgressPacket), UpdateProgressPacket::create,
        L"UpdateProgress");
    map(157, true, true, true, false, typeid(TextureChangePacket), TextureChangePacket::create,
        L"TextureChange");
    map(158, true, false, true, false, typeid(UpdateGameRuleProgressPacket),
        UpdateGameRuleProgressPacket::create, L"UpdateGameRuleProgress");
    map(159, false, true, false, false, typeid(KickPlayerPacket), KickPlayerPacket::create, L"KickPlayer");
    map(160, true, true, true, false, typeid(TextureAndGeometryPacket), TextureAndGeometryPacket::create,
        L"TextureAndGeometry");
    map(161, true, true, true, false, typeid(TextureAndGeometryChangePacket),
        TextureAndGeometryChangePacket::create, L"TextureAndGeometryChange");
    map(162, true, false, false, false, typeid(MoveEntityPacketSmall), MoveEntityPacketSmall::create,
        L"MoveEntityPacketSmall");
    map(163, true, false, false, false, typeid(MoveEntityPacketSmall::Pos),
        MoveEntityPacketSmall::Pos::create, L"MoveEntityPacketSmall");
    map(164, true, false, false, false, typeid(MoveEntityPacketSmall::Rot),
        MoveEntityPacketSmall::Rot::create, L"MoveEntityPacketSmall");
    map(165, true, false, false, false, typeid(MoveEntityPacketSmall::PosRot),
        MoveEntityPacketSmall::PosRot::create, L"MoveEntityPacketSmall");
    map(166, true, true, false, false, typeid(XZPacket), XZPacket::create, L"XZ");
    map(167, false, true, false, false, typeid(GameCommandPacket), GameCommandPacket::create, L"GameCommand");
    map(168, true, false, false, false, typeid(MapSelectInfoPacket), MapSelectInfoPacket::create,
        L"MapSelectInfo");
    map(169, true, true, false, false, typeid(VotePacket), VotePacket::create, L"Vote");
    map(170, true, true, false, false, typeid(PlayerReadyPacket), PlayerReadyPacket::create, L"PlayerReady");
    map(171, true, false, true, false, typeid(ClientboundPowerupPacket), ClientboundPowerupPacket::create,
        L"Powerup");
    map(200, true, false, true, false, typeid(ClientboundAwardStatPacket), ClientboundAwardStatPacket::create,
        L"AwardStat");
    map(201, true, true, false, false, typeid(PlayerInfoPacket), PlayerInfoPacket::create, L"PlayerInfo");
    map(202, true, true, true, false, typeid(ClientboundPlayerAbilitiesPacket),
        ClientboundPlayerAbilitiesPacket::create, L"PlayerAbilities");
    map(205, false, true, true, false, typeid(ServerboundClientCommandPacket),
        ServerboundClientCommandPacket::create, L"ClientCommand");
    map(206, true, false, true, false, typeid(ScoreboardPacket), ScoreboardPacket::create, L"Scoreboard");
    map(209, true, true, false, false, typeid(ClientboundSetPlayerTeamPacket),
        ClientboundSetPlayerTeamPacket::create, L"SetPlayerTeam");
    map(210, true, true, true, false, typeid(GameModePacket), GameModePacket::create, L"GameMode");
    map(211, true, false, true, false, typeid(ClientboundMapItemDataPacket),
        ClientboundMapItemDataPacket::create, L"MapItemData");
    map(212, true, false, true, false, typeid(ClientboundOpenSignEditorPacket),
        ClientboundOpenSignEditorPacket::create, L"OpenSignEditor");
    map(213, true, false, true, false, typeid(ClientboundPlayerCombatPacket),
        ClientboundPlayerCombatPacket::create, L"PlayerCombat");
    map(214, true, false, true, false, typeid(ClientboundPlayerPositionPacket),
        ClientboundPlayerPositionPacket::create, L"PlayerPosition");
    map(216, true, false, false, false, typeid(ClientboundResourcePackPacket),
        ClientboundResourcePackPacket::create, L"ResourcePack");
    map(217, true, false, true, false, typeid(ClientboundSetBorderPacket), ClientboundSetBorderPacket::create,
        L"SetBorder");
    map(218, true, false, false, false, typeid(ClientboundSetCameraPacket),
        ClientboundSetCameraPacket::create, L"SetCamera");
    map(219, true, false, true, false, typeid(ClientboundSetTitlesPacket), ClientboundSetTitlesPacket::create,
        L"SetTitles");
    map(220, true, false, true, false, typeid(ClientboundTabListPacket), ClientboundTabListPacket::create,
        L"TabList");
    map(221, false, true, false, false, typeid(ServerboundChatAutoCompletePacket),
        ServerboundChatAutoCompletePacket::create, L"ChatAutoComplete");
    map(222, false, true, false, false, typeid(ServerboundChatPacket), ServerboundChatPacket::create,
        L"Chat");
    map(223, false, true, false, false, typeid(ServerboundContainerAckPacket),
        ServerboundContainerAckPacket::create, L"ContainerAck");
    map(224, false, true, false, false, typeid(ServerboundContainerClosePacket),
        ServerboundContainerClosePacket::create, L"ContainerClose");
    map(225, false, true, false, false, typeid(ServerboundCustomPayloadPacket),
        ServerboundCustomPayloadPacket::create, L"CustomPayload");
    map(226, false, true, false, false, typeid(ServerboundKeepAlivePacket),
        ServerboundKeepAlivePacket::create, L"KeepAlive");
    map(227, false, true, false, false, typeid(ServerboundPlayerAbilitiesPacket),
        ServerboundPlayerAbilitiesPacket::create, L"PlayerAbilities");
    map(228, false, true, false, false, typeid(ServerboundResourcePackPacket),
        ServerboundResourcePackPacket::create, L"ResourcePack");
    map(229, false, true, false, false, typeid(ServerboundSetCarriedItemPacket),
        ServerboundSetCarriedItemPacket::create, L"SetCarriedItem");
    map(230, false, true, false, false, typeid(ServerboundSignUpdatePacket),
        ServerboundSignUpdatePacket::create, L"SignUpdate");
    map(231, false, true, false, false, typeid(ServerboundTeleportToEntityPacket),
        ServerboundTeleportToEntityPacket::create, L"TeleportToEntity");
    map(232, false, true, false, false, typeid(ServerboundPreLoginPacket), ServerboundPreLoginPacket::create,
        L"PreLogin");
    map(233, false, true, false, false, typeid(ServerboundSwingPacket), ServerboundSwingPacket::create,
        L"Swing");
    map(234, true, false, true, false, typeid(ClientboundDamageIndicatorPacket),
        ClientboundDamageIndicatorPacket::create, L"DamageIndicator");
    map(235, true, false, false, false, typeid(ClientboundBlockCollectionDestructionPacket),
        ClientboundBlockCollectionDestructionPacket::create, L"BlockCollectionDestruction");
    map(236, true, false, true, false, typeid(ClientboundCooldownPacket), ClientboundCooldownPacket::create,
        L"Cooldown");
    map(239, true, false, true, false, typeid(ClientboundMGPlayerSettingsUpdatePacket),
        ClientboundMGPlayerSettingsUpdatePacket::create, L"MiniGameSettingsUpdate");
    map(250, true, true, true, false, typeid(ClientboundCustomPayloadPacket),
        ClientboundCustomPayloadPacket::create, L"CustomPayload");
    map(253, true, false, false, false, typeid(ClientboundChangeDifficultyPacket),
        ClientboundChangeDifficultyPacket::create, L"ChangeDifficulty");
    map(254, false, true, false, false, typeid(GetInfoPacket), GetInfoPacket::create, L"GetInfo");
    map(255, true, true, true, false, typeid(DisconnectPacket), DisconnectPacket::create, L"Disconnect");
}
