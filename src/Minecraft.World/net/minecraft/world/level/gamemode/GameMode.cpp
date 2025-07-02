#include "Minecraft.World/level/gamemode/GameMode.h"
#include "Minecraft.World/level/gamemode/GameType.h"

#include "Minecraft.Client/Minecraft.h"

GameMode::GameMode() {
    mGameType = nullptr;
    mMinecraft = Minecraft::GetInstance();
}

GameMode::~GameMode() {}

bool GameMode::CanRecordStatsAndAchievements() {
    return mGameType != GameType::CREATIVE && !isSpectator();
}

void GameMode::RecordDamage(std::shared_ptr<Entity>, CombatEntry*, std::shared_ptr<ClientboundChatPacket>) {}

void GameMode::RecordDeath(std::shared_ptr<Entity>) {}

void GameMode::RecordItem(not_null_ptr<ItemInstance>) {}

void GameMode::RecordContainer(int, int, int, int) {}

void GameMode::RecordWalk(int, bool, bool) {}

void GameMode::RecordSwim(int, bool) {}

void GameMode::RecordClimb(int) {}

void GameMode::RecordUseItem(not_null_ptr<ItemInstance>) {}

void GameMode::RecordJump() {}

void GameMode::RecordGainPoints(int) {}

void GameMode::ResetTempPoints() {}

bool GameMode::RecordSecondaryTargetReached(const std::wstring&, int, GlideRingGenerator::eGlideRingSize) {
    return false;
}

bool GameMode::RecordLastCheckpoint(int, int, bool, bool, bool) {
    return false;
}

bool GameMode::RecordLapCompleted() {
    return false;
}

void GameMode::RecordThermalEntered() {}

bool GameMode::RecordProgress(double, double, double, double) {
    return false;
}

void GameMode::RecordSpawnedAtCheckpoint(int) {}

void GameMode::RecordBlockPlaced(const BlockPos&, int) {}

void GameMode::RecordBlockDestroyed(const BlockPos&, int) {}

void GameMode::RecordBlockPresent(const BlockPos&, int) {}

void GameMode::RecordLayerTime() {}

void GameMode::RecordSnowballHit() {}

void GameMode::RecordHitBySnowball() {}

void GameMode::RecordLanding(const BlockPos&) {}

void GameMode::OnMouseDown() {}

bool GameMode::isSpectator() {
    return mGameType == GameType::SPECTATOR;
}
