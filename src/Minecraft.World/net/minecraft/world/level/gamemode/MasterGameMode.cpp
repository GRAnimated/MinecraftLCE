#include "net/minecraft/world/level/gamemode/MasterGameMode.h"

#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/client/multiplayer/ServerGamePacketListenerImpl.h"
#include "net/minecraft/network/protocol/game/ClientboundChatPacket.h"
#include "net/minecraft/network/protocol/game/GameModePacket.h"
#include "net/minecraft/server/MinecraftServer.h"
#include "net/minecraft/server/ServerLevel.h"
#include "net/minecraft/server/players/PlayerList.h"
#include "net/minecraft/world/entity/EquipmentSlot.h"
#include "net/minecraft/world/entity/item/EnderCrystal.h"
#include "net/minecraft/world/entity/player/ServerPlayer.h"
#include "net/minecraft/world/item/ElytraItem.h"
#include "net/minecraft/world/item/ItemInstance.h"
#include "net/minecraft/world/item/Items.h"
#include "net/minecraft/world/level/LevelRuleset.h"
#include "net/minecraft/world/level/gamemode/BlockDegradeRoutine.h"
#include "net/minecraft/world/level/gamemode/CommonMasterGameMode.h"
#include "net/minecraft/world/level/gamemode/ConsoleGameRules.h"
#include "net/minecraft/world/level/gamemode/GameStats.h"
#include "net/minecraft/world/level/gamemode/minigames/EMiniGameId.h"
#include "net/minecraft/world/level/gamemode/minigames/MiniGameDef.h"
#include "net/minecraft/world/level/gamemode/minigames/glide/rules/CheckpointRuleDefinition.h"
#include "net/minecraft/world/level/gamemode/minigames/glide/rules/PowerupRuleDefinition.h"
#include "net/minecraft/world/level/gamemode/minigames/glide/rules/TargetAreaRuleDefinition.h"
#include "net/minecraft/world/level/gamemode/rules/DegradationSequenceRuleDefinition.h"
#include "net/minecraft/world/level/gamemode/rules/GameRuleDefinition.h"
#include "net/minecraft/world/level/gamemode/rules/OnInitialiseWorld.h"
#include "types.h"
#include <memory>
#include <vector>

void MasterGameMode::PopulateChests() {
    LevelRuleset* rules = CConsoleMinecraftApp::sInstance.getGameRuleDefinitions();
    if (rules) {
        OnInitialiseWorld* initWorld
            = (OnInitialiseWorld*)rules->getRuleByType(ConsoleGameRules::EGameRuleType_OnInitialiseWorld);

        if (initWorld) {
            ServerLevel* level = MinecraftServer::getInstance()->getLevel(0);
            std::vector<GameRuleDefinition*> vector;

            initWorld->getChildren(&vector, ConsoleGameRules::EGameRuleType_PlaceContainer);
            if (!vector.empty()) {
                for (auto it = vector.begin(); it != vector.end(); it++) {
                    (*it)->evaluateRule(level, rules, *CommonMasterGameMode::GetMiniGame());
                }
                vector.clear();
            }

            initWorld->getChildren(&vector, ConsoleGameRules::EGameRuleType_DistributeItems);
            if (!vector.empty()) {
                for (auto it = vector.begin(); it != vector.end(); it++) {
                    (*it)->evaluateRule(level, rules, *CommonMasterGameMode::GetMiniGame());
                }
                vector.clear();
            }

            initWorld->getChildren(&vector, ConsoleGameRules::EGameRuleType_PopulateContainer);
            if (!vector.empty()) {
                for (auto it = vector.begin(); it != vector.end(); it++) {
                    (*it)->evaluateRule(level, rules, *CommonMasterGameMode::GetMiniGame());
                }
            }
        }
    }
}

void MasterGameMode::SetLockPlayerPositions(bool lock) {
    const GameModePacket::LockPlayerLocation emptyData(lock);
    MinecraftServer::tryGetPlayers()->broadcastAll(
        GameModePacket::Create((GameModePacket::EMessage)0x13, emptyData));

    std::vector<std::shared_ptr<ServerPlayer>>* players = MinecraftServer::tryGetPlayers()->getPlayers();
    for (auto it = players->begin(); it != players->end(); it++) {
        std::shared_ptr<ServerPlayer> player = *it;
        player->SetPositionLocked(lock);
    }
}

Team* teamek;

// TODO: implement this (this is random shit to match other functions), this have to be implemented here
// until we introduce Unity builds
const AABB* CommonMasterGameMode::GetTeamArea(Team* team) const {
    teamek = team;
    return AABB::newTemp(0, 0, 0, 0, 0, 0);
}

void MasterGameMode::OnGameStart(MasterGameMode* _this, void*) {
    const MiniGameDef* minigame = CommonMasterGameMode::GetMiniGame();
    LevelRuleset* rules = CConsoleMinecraftApp::sInstance.getLevelGenerationOptions()->getRequiredGameRules();

    MinecraftServer::getInstance()->tryGetPlayers()->broadcastAll(std::shared_ptr<ClientboundChatPacket>(
        new ClientboundChatPacket(ClientboundChatPacket::EChatPacketMessage_RoundStart, -1)));

    _this->PopulateChests();

    if (CommonMasterGameMode::GetMiniGame()->GetId() == EMiniGameId::GLIDE) {
        ServerLevel* level = MinecraftServer::getInstance()->getLevel(0);
        if (minigame->ArePowerupsActive()) {
            std::vector<PowerupRuleDefinition*> powerupRules;
            rules->getPowerups(&powerupRules);
            for (auto it = powerupRules.begin(); it != powerupRules.end(); it++) {
                PowerupRuleDefinition* rule = *it;
                std::vector<std::shared_ptr<Entity>>* entities
                    = level->getEntitiesOfClass(typeid(EnderCrystal), rule->getArea());
                if (entities->end() == entities->begin()) {
                    std::shared_ptr<EnderCrystal> crystal = std::shared_ptr<EnderCrystal>(
                        new EnderCrystal(level, rule->getArea()->getCenter()->x,
                                         rule->getArea()->getCenter()->y, rule->getArea()->getCenter()->z));
                    crystal->setShowBottom(false);
                    level->addEntity(crystal);
                }
            }
        }
        std::vector<std::shared_ptr<ServerPlayer>>* players
            = MinecraftServer::getInstance()->tryGetPlayers()->getPlayers();
        for (auto it = players->begin(); it != players->end(); it++) {
            std::shared_ptr<ServerPlayer> player = *it;
            not_null_ptr<ItemInstance> player_chest = player->getItemSlot(EquipmentSlot::CHEST);
            if (player_chest->getItem() == Items::ELYTRA) {
                if (ElytraItem::isFlyEnabled(player_chest)) {
                    const AABB* area = rules->getNamedArea(L"JumpOffPoint");
                    if (!area || !area->containsIncludingLowerBound(player->getPos(1.0))) {
                        player->startFallFlying();
                    }
                }
            }
        }

        _this->setCheckpoints(*rules->getCheckpoints());
        for (auto it = _this->mGlideCheckpoints.begin(); it != _this->mGlideCheckpoints.end(); it++) {
            (*it)->processBeacons(level);
        }

        _this->mGlideTargets.clear();

        std::vector<TargetAreaRuleDefinition*> targetAreas;
        rules->getTargetAreas(&targetAreas);
        for (auto it = targetAreas.begin(); it != targetAreas.end(); it++) {
            if ((*it)->isPrimary()) {
                _this->mGlideTargets.push_back((*it)->getArea());
            }
        }
    }

    _this->SetLockPlayerPositions(false);

    {
        std::vector<NamedAreaRuleDefinition*> playerBounds;
        rules->getPlayerBoundsVolumes(&playerBounds);

        std::vector<std::shared_ptr<ServerPlayer>>* players
            = MinecraftServer::getInstance()->tryGetPlayers()->getPlayers();
        for (auto it = players->begin(); it != players->end(); it++) {
            std::shared_ptr<ServerPlayer>& player = *it;
            const GameModePacket::EmptyData emptyData;
            player->mConnection->send(GameModePacket::Create((GameModePacket::EMessage)0xF, emptyData));

            Team* team = player->getTeam();
            if (minigame->GetId() == EMiniGameId::BUILD_OFF && team) {
                const AABB* teamArea = _this->GetTeamArea(team);
                if (teamArea) {
                    teamArea = teamArea->grow(0, 1, 0);
                    const GameModePacket::AddAreaBoundsData areaBoundsData
                        = GameModePacket::AddAreaBoundsData(teamArea->min.x, teamArea->min.y, teamArea->min.z,
                                                            teamArea->max.x, teamArea->max.y,
                                                            teamArea->max.z);
                    player->mConnection->send(
                        GameModePacket::Create((GameModePacket::EMessage)0xD, areaBoundsData));
                }

            } else {
                for (auto it = playerBounds.begin(); it != playerBounds.end(); it++) {
                    const AABB* area = (*it)->getArea();
                    const GameModePacket::AddAreaBoundsData areaBoundsData
                        = GameModePacket::AddAreaBoundsData(area->min.x, area->min.y, area->min.z,
                                                            area->max.x, area->max.y, area->max.z);

                    player->mConnection->send(
                        GameModePacket::Create((GameModePacket::EMessage)0xD, areaBoundsData));
                }
            }
        }
    }

    _this->SetState((MasterGameMode::EInternalGameModeState)10);
    _this->sendTutorialUpdate((eTutorial_GameMode)3);

    if (minigame->GetId() == EMiniGameId::BATTLE) {
        CountdownInfo* chestRefilTimer = new CountdownInfo();
        chestRefilTimer->mInt_0 = 0;
        chestRefilTimer->mOnTimerFunc1 = MasterGameMode::OnRefillChestTimer;

        _this->AddTimer(MasterGameMode::ChestRefill, OnTimerCountdown, chestRefilTimer, -1, 30000, -1, -1);
    }

    LevelRuleset* gameRules = CConsoleMinecraftApp::sInstance.getGameRuleDefinitions();
    if (gameRules) {
        DegradationSequenceRuleDefinition* degradeRule
            = (DegradationSequenceRuleDefinition*)gameRules->getRuleByType(
                ConsoleGameRules::EGameRuleType_DegradationSequence);
        if (degradeRule) {
            _this->mDegradeRoutine
                = new BlockDegradeRoutine(MinecraftServer::getInstance()->getLevel(0), degradeRule);
        }
    }

    CountdownInfo* gracePeriod = new CountdownInfo();
    gracePeriod->mInt_0 = 123;
    gracePeriod->mOnTimerFunc = MasterGameMode::OnGracePeriodEnd;
    if (_this->StartTimer(MasterGameMode::GracePeriod, gracePeriod)) {
        if (_this->GetTimerRemainingTime(MasterGameMode::GracePeriod) >= 1) {
            _this->sendTutorialUpdate((eTutorial_GameMode)2);
        }
    } else {
        delete gracePeriod;
        _this->SetPlayersInvulnerable(false);
    }

    _this->GetGameStats()->OnRoundStart();
}
