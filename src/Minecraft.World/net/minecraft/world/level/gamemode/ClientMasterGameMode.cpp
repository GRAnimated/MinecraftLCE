#include "ClientMasterGameMode.h"

bool ClientMasterGameMode::isNewLevelDataPending() {
    return m_hasPendingLevelData;
}