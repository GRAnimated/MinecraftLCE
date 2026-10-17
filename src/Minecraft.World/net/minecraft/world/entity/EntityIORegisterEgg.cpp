#include "net/minecraft/world/entity/EntityIO.h"

EntityIO::SpawnEggInfo EntityIO::registerEgg(std::uint32_t hash, const std::wstring name, int primaryColor,
                                             int secondaryColor) {
    ResourceLocation key(name);
    SPAWN_EGGS[key] = new SpawnEggInfo(hash, key, primaryColor, secondaryColor);
    return *SPAWN_EGGS[key];
}
