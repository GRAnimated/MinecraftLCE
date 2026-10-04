#include "net/minecraft/world/level/gamemode/ClientMasterGameMode.h"

bool ClientMasterGameMode::isNewLevelDataPending() {
    return m_hasPendingLevelData;
}
