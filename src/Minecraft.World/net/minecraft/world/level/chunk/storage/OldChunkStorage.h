#pragma once
#include "com/mojang/nbt/CompoundTag.h"
#include "net/minecraft/core/io/DataOutputStream.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/chunk/LevelChunk.h"

class OldChunkStorage {
#define CHUNK_VERSION 11
public:
    /** Saves using the older McRegion style chunk format */
    static void save(LevelChunk* chunk, Level* lvl, CompoundTag* tag);
    /** Saves using the new chunk format */
    static void save(LevelChunk* chunk, Level* lvl, DataOutputStream* stream);

    static void CreateNewThreadStorage();

    class ThreadStorage {};
};