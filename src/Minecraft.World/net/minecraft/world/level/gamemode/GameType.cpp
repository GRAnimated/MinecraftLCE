#include "net/minecraft/world/level/gamemode/GameType.h"

#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/world/entity/player/Abilities.h"

GameType* GameType::NOT_SET;
GameType* GameType::SURVIVAL;
GameType* GameType::CREATIVE;
GameType* GameType::ADVENTURE;
GameType* GameType::SPECTATOR;
GameType* GameType::LOBBY;

void GameType::staticCtor() {
    NOT_SET = new GameType(-1, L"", L"", -1, -1);
    SURVIVAL = new GameType(0, L"survival", L"s", StringIDs::Survival, StringIDs::GameModeSurvival);
    CREATIVE = new GameType(1, L"creative", L"c", StringIDs::Creative_1, StringIDs::GameModeCreative);
    ADVENTURE = new GameType(2, L"adventure", L"a", StringIDs::Adventure, StringIDs::GameModeAdventure);
    SPECTATOR = new GameType(3, L"spectator", L"sp", -1, -1);
    LOBBY = new GameType(4, L"lobby", L"l", -1, -1);
}

GameType::GameType(int id, const std::wstring& label, const std::wstring& sliderLabel, int a5, int a6) {
    mId = id;
    mLabel = label;
    mSliderLabel = sliderLabel;
    field_38 = a5;
    field_3C = a6;
}

int GameType::getId() const {
    return mId;
}

int GameType::getLabel() const {
    return field_38;
}

int GameType::getSliderLabel() const {
    return field_3C;
}

bool GameType::isBlockPlacingRestricted() const {
    return ADVENTURE == this || SPECTATOR == this || LOBBY == this;
}

// NON_MATCHING: aaaaahahahaha this is so fucked
void GameType::updatePlayerAbilities(Abilities* abilities) const {
    if (CREATIVE == this) {
        abilities->mIsEnableFly = true;
        abilities->mIsInstabuild = true;
        abilities->mIsInvulnerable = true;
    } else {
        bool test;
        if (SPECTATOR == this) {
            test = true;
            abilities->mIsEnableFly = true;
            abilities->mIsInstabuild = false;
            abilities->mIsInvulnerable = true;
        } else {
            GameType* lobbyType = LOBBY;
            abilities->mIsEnableFly = false;
            abilities->mIsInstabuild = false;
            if (lobbyType == this) {
                test = false;
                abilities->mIsInvulnerable = true;
            } else {
                test = false;
                abilities->mIsFlying = false;
                abilities->mIsInvulnerable = false;
            }
            abilities->mIsFlying = test;
        }
    }
    abilities->mIsEnableBuild = !isBlockPlacingRestricted();
}

bool GameType::isCreative() const {
    return CREATIVE == this || LOBBY == this;
}

bool GameType::isSurvival() const {
    return SURVIVAL == this || ADVENTURE == this;
}

const GameType* GameType::byId(int id, const GameType* gameType) {
    if (NOT_SET->mId == id)
        return NOT_SET;
    if (SURVIVAL->mId == id)
        return SURVIVAL;
    if (CREATIVE->mId == id)
        return CREATIVE;
    if (ADVENTURE->mId == id)
        return ADVENTURE;
    if (SPECTATOR->mId == id)
        return SPECTATOR;
    if (LOBBY->mId == id)
        return LOBBY;
    return gameType;
}

const GameType* GameType::byId(int id) {
    return byId(id, SURVIVAL);
}
