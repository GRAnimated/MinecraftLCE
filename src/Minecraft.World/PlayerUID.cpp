#include "Minecraft.World/PlayerUID.h"

#include <cstring>

PlayerUID::PlayerUID(int uid) {
    memset(mUIDParts, 0, sizeof(mUIDParts));
}
