#include "net/minecraft/world/entity/EntityIO.h"

// name guessed
EntityIO::SpawnEggInfo::SpawnEggInfo(std::uint32_t value, const ResourceLocation& name, int primary,
                                     int secondary) {
    hash = value;
    key = ResourceLocation(name);
    primaryColor = primary;
    secondaryColor = secondary;
    unknown96 = 0;
    unknown104 = 0;
}

// name guessed
EntityIO::SpawnEggInfo::SpawnEggInfo(const SpawnEggInfo& other) : hash(other.hash), key(other.key) {
    unknown104 = other.unknown104;
    unknown96 = other.unknown96;
    colors = other.colors;
}

// name guessed
EntityIO::SpawnEggInfo::~SpawnEggInfo() {}
