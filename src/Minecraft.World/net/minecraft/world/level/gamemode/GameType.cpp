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
    m_id = id;
    m_label = label;
    m_sliderLabel = sliderLabel;
    m_field38 = a5;
    m_field3C = a6;
}

int GameType::getId() const {
    return m_id;
}

int GameType::getLabel() const {
    return m_field38;
}

int GameType::getSliderLabel() const {
    return m_field3C;
}

bool GameType::isBlockPlacingRestricted() const {
    return ADVENTURE == this || SPECTATOR == this || LOBBY == this;
}

// NON_MATCHING: aaaaahahahaha this is so fucked
void GameType::updatePlayerAbilities(Abilities* abilities) const {
    if (CREATIVE == this) {
        abilities->m_isEnableFly = true;
        abilities->m_isInstabuild = true;
        abilities->m_isInvulnerable = true;
    } else {
        bool test;
        if (SPECTATOR == this) {
            test = true;
            abilities->m_isEnableFly = true;
            abilities->m_isInstabuild = false;
            abilities->m_isInvulnerable = true;
        } else {
            GameType* lobbyType = LOBBY;
            abilities->m_isEnableFly = false;
            abilities->m_isInstabuild = false;
            if (lobbyType == this) {
                test = false;
                abilities->m_isInvulnerable = true;
            } else {
                test = false;
                abilities->m_isFlying = false;
                abilities->m_isInvulnerable = false;
            }
            abilities->m_isFlying = test;
        }
    }
    abilities->m_isEnableBuild = !isBlockPlacingRestricted();
}

bool GameType::isCreative() const {
    return CREATIVE == this || LOBBY == this;
}

bool GameType::isSurvival() const {
    return SURVIVAL == this || ADVENTURE == this;
}

const GameType* GameType::byId(int id, const GameType* gameType) {
    if (NOT_SET->m_id == id)
        return NOT_SET;
    if (SURVIVAL->m_id == id)
        return SURVIVAL;
    if (CREATIVE->m_id == id)
        return CREATIVE;
    if (ADVENTURE->m_id == id)
        return ADVENTURE;
    if (SPECTATOR->m_id == id)
        return SPECTATOR;
    if (LOBBY->m_id == id)
        return LOBBY;
    return gameType;
}

const GameType* GameType::byId(int id) {
    return byId(id, SURVIVAL);
}
