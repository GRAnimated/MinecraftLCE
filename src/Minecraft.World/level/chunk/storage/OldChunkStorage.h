#pragma once
#include "Minecraft.Core/io/DataOutputStream.h"

class LevelChunk;
class Level;
class CompoundTag;

class OldChunkStorage {
    public:
    static void save(LevelChunk *chunk, Level *lvl, CompoundTag *tag);
    static void save(LevelChunk *chunk, Level *lvl, DataOutputStream *stream);
};