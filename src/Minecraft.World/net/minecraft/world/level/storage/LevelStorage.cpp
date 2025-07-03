#include "net/minecraft/world/level/storage/LevelStorage.h"

#include "net/minecraft/world/PlayerUID.h"

LevelStorage::LevelStorage() {}

// NON_MATCHING: D0 destructor
LevelStorage::~LevelStorage() = default;

ConsoleSaveFile* LevelStorage::getSaveFile() {
    return nullptr;
}

void LevelStorage::flushSaveFile(bool) {}

int LevelStorage::getAuxValueForMap(PlayerUID, int, int, int, int) {
    return 0;
}
