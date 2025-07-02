#include "Minecraft.World/PlayerUID.h"

#include <cstring>

PlayerUID::PlayerUID(int uid) {
    memset(this, 0, sizeof(PlayerUID));
}
