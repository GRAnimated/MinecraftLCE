#include "Minecraft.World/level/gamemode/GameType.h"

#include "Minecraft.World/entity/player/Abilities.h"

void GameType::staticCtor() {
    NOT_SET = new GameType(-1, L"", L"", -1, -1);
    SURVIVAL = new GameType(0, L"survival", L"s", 0x15AA0E94, 0x9BA782A6);
    CREATIVE = new GameType(1, L"creative", L"c", 0xB7C2FCAF, 0x12D696DD);
    ADVENTURE = new GameType(2, L"adventure", L"a", 0xA48E97FA, 0xF9915358);
    SPECTATOR = new GameType(3, L"spectator", L"sp", -1, -1);
    LOBBY = new GameType(4, L"lobby", L"l", -1, -1);
}

GameType::GameType(int id, const std::wstring& label, const std::wstring& sliderLabel, int field_38, int field_3C) {
    mId = id;
    mLabel = label;
    mSliderLabel = sliderLabel;
    this->field_38 = field_38;
    this->field_3C = field_3C;
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
        abilities->isEnableFly = true;
        abilities->isInstabuild = true;
        abilities->isInvulnerable = true;
    } else {
        bool test;
        if (SPECTATOR == this) {
            test = true;
            abilities->isEnableFly = true;
            abilities->isInstabuild = false;
            abilities->isInvulnerable = true;
        } else {
            GameType* lobbyType = LOBBY;
            abilities->isEnableFly = false;
            abilities->isInstabuild = false;
            if (lobbyType == this) {
                test = false;
                abilities->isInvulnerable = true;
            } else {
                test = false;
                abilities->isFlying = false;
                abilities->isInvulnerable = false;
            }
            abilities->isFlying = test;
        }
    }
    abilities->isEnableBuild = !this->isBlockPlacingRestricted();
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
