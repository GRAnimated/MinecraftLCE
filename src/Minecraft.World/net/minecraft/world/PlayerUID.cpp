#include "net/minecraft/world/PlayerUID.h"

#include <cstring>

PlayerUID::PlayerUID(int uid) {
    memset(this, 0, sizeof(PlayerUID));
}
