#include "net/minecraft/world/entity/player/Player.h"

#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/client/eGameHostOption.h"
#include "net/minecraft/world/level/Level.h"

bool Player::isAllowedToFly() {
    return CConsoleMinecraftApp::sInstance.GetGameHostOption(static_cast<eGameHostOption>(16))
           && getPlayerGamePrivilege(static_cast<EPlayerGamePrivileges>(5));
}

bool Player::hasInvulnerablePrivilege() {
    return CConsoleMinecraftApp::sInstance.GetGameHostOption(static_cast<eGameHostOption>(18))
           && getPlayerGamePrivilege(static_cast<EPlayerGamePrivileges>(8));
}

void Player::causeFoodExhaustion(float exhaustion) {
    if (usesLegacyFoodHealing() || (isAllowedToFly() && m_abilities.m_isFlying)
        || m_abilities.m_isInvulnerable || hasInvulnerablePrivilege()) {
        return;
    }
    if ((CConsoleMinecraftApp::sInstance.GetGameHostOption(static_cast<eGameHostOption>(12))
         || !getPlayerGamePrivilege(static_cast<EPlayerGamePrivileges>(1)))
        && !m_level->m_isLocal) {
        m_foodData.addExhaustion(exhaustion);
    }
}

FoodData* Player::getFoodData() {
    return &m_foodData;
}

bool Player::usesLegacyFoodHealing() {
    return CConsoleMinecraftApp::sInstance.GetGameHostOption(static_cast<eGameHostOption>(17))
           && getPlayerGamePrivilege(static_cast<EPlayerGamePrivileges>(6));
}

bool Player::isHurt() {
    return getHealth() > 0.0f && getHealth() < getMaxHealth();
}
