#include "net/minecraft/core/System.h"
#include "net/minecraft/server/ServerLevel.h"
#include "net/minecraft/server/level/ServerChunkCache.h"
#include "net/minecraft/world/level/chunk/ChunkGenerator.h"
#include "net/minecraft/world/level/chunk/EmptyLevelChunk.h"

ServerChunkCache::ServerChunkCache(ServerLevel* level, ChunkStorage* storage, ChunkGenerator* generator) {
    int size = generator->getSize();
    int _2;
    if (size > 0)
        _2 = size;
    else
        _2 = size + 1;
    dword_b8 = size;
    dword_bc = _2 / 2;
    mXZSize = size;
    byte_28 = false;

    mBorderChunk = new EmptyLevelChunk(level, 0, 0);
    mLevel = level;
    mDimension = level->mDimension;
    mChunkGenerator = generator;
    mChunkStorage = storage;

    field_30 = new LevelChunk*[_2 * _2];
    field_90 = new LevelChunk*[_2 * _2];

    qword_c0 = nullptr;
    qword_c8 = nullptr;

    InitializeCriticalSectionAndSpinCount(&mMutex, 4000);
}
