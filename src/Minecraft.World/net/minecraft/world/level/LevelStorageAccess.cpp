#include "net/minecraft/world/level/Level.h"

LevelStorage* Level::getLevelStorage() {
    return m_levelStorage.get();
}
