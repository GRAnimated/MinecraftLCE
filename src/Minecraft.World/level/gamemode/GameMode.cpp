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
