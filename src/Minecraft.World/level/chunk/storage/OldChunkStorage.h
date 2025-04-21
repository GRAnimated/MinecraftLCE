#pragma once
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.Nbt/CompoundTag.h"
#include "Minecraft.World/level/Level.h"
#include "Minecraft.World/level/chunk/LevelChunk.h"

class OldChunkStorage {
#define CHUNK_VERSION 11
    public:
    /** Saves using the older McRegion style chunk format */
    static void save(LevelChunk *chunk, Level *lvl, CompoundTag *tag);
    /** Saves using the new chunk format */
    static void save(LevelChunk *chunk, Level *lvl, DataOutputStream *stream);
};