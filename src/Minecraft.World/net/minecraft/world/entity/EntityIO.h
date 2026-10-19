#pragma once

#include "net/minecraft/resources/ResourceLocation.h"
#include <cstdint>
#include <string>
#include <unordered_map>
#include <unordered_set>

class Entity;
class Level;

class EntityIO {
public:
    struct SpawnEggInfo {
        SpawnEggInfo(std::uint32_t, const ResourceLocation&, int, int);
        SpawnEggInfo(const SpawnEggInfo&);
        ~SpawnEggInfo();

        std::uint32_t hash;
        ResourceLocation key;
        union {
            std::uint64_t colors;
            struct {
                int primaryColor;
                int secondaryColor;
            };
        };
        std::uint64_t unknown96;
        std::uint64_t unknown104;
    };

    static void bootStrap();
    static ResourceLocation getKey(eINSTANCEOF);
    static void registerEntity(Entity* (*)(Level*), int, const std::wstring&, eINSTANCEOF,
                               const std::wstring&);
    static SpawnEggInfo registerEgg(std::uint32_t, const std::wstring, int, int);

    static std::unordered_map<ResourceLocation, SpawnEggInfo*> SPAWN_EGGS;
    static ResourceLocation DEFAULT_TYPE;
    static std::unordered_set<ResourceLocation> KNOWN_TYPES;
};

#ifdef SAFETY_CHECKS
static_assert(sizeof(EntityIO::SpawnEggInfo) == 112, "Spawn egg metadata layout");
static_assert(offsetof(EntityIO::SpawnEggInfo, key) == 8, "Spawn egg resource key");
static_assert(offsetof(EntityIO::SpawnEggInfo, colors) == 88, "Spawn egg colors");
static_assert(offsetof(EntityIO::SpawnEggInfo, unknown104) == 104, "Spawn egg tail");
#endif
