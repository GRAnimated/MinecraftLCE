#pragma once
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.Nbt/CompoundTag.h"
#include "Minecraft.World/level/Level.h"
#include "Minecraft.World/level/chunk/LevelChunk.h"

class OldChunkStorage {
    public:
    static void save(LevelChunk *chunk, Level *lvl, CompoundTag *tag);
    static void save(LevelChunk *chunk, Level *lvl, DataOutputStream *stream);
};