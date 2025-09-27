#include "net/minecraft/world/PlayerUID.h"

#include <cstring>

PlayerUID::PlayerUID(int uid) {
    memset(this, 0, sizeof(PlayerUID));
}
bool PlayerUID::operator!=(const PlayerUID& other) const {
    return !(*this == other);
}
