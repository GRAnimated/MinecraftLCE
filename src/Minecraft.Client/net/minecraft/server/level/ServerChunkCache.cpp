#include "net/minecraft/server/level/ServerChunkCache.h"

#include "NX/Platform.h"

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/core/System.h"
#include "net/minecraft/server/MinecraftServer.h"
#include "net/minecraft/server/ServerLevel.h"
#include "net/minecraft/world/level/chunk/ChunkGenerator.h"
#include "net/minecraft/world/level/chunk/EmptyLevelChunk.h"
#include "net/minecraft/world/level/chunk/LevelChunk.h"
#include "net/minecraft/world/level/chunk/storage/ChunkStorage.h"
#include "net/minecraft/world/level/dimension/Dimension.h"

#include <nn/os/os_Mutex.h>

ServerChunkCache::ServerChunkCache(ServerLevel* level, ChunkStorage* storage, ChunkGenerator* generator) {
    int size = generator->getSize();
    dword_bc = size / 2;
    dword_b8 = size;
    mXZSize = size;
    byte_28 = false;

    mEmptyChunk = new EmptyLevelChunk(level, 0, 0);

    mDimension = level->mDimension;
    mLevel = level;
    mChunkGenerator = generator;
    mChunkStorage = storage;

    mChunks = new LevelChunk*[dword_b8 * dword_b8];
    memset(mChunks, 0, dword_b8 * dword_b8 * sizeof(LevelChunk*));

    mUnloadedChunks = new LevelChunk*[dword_b8 * dword_b8];
    memset(mUnloadedChunks, 0, dword_b8 * dword_b8 * sizeof(LevelChunk*));

    mContainsChunkFunc = nullptr;
    qword_c8 = nullptr;

    InitializeCriticalSectionAndSpinCount(&mMutex, 4000);
}

ServerChunkCache::~ServerChunkCache() {
    mChunkStorage->WaitForAll();

    delete mChunkStorage;
    delete mEmptyChunk;
    delete mChunks;
    delete mChunkGenerator;

    for (int i = 0; i < dword_b8 * dword_b8; ++i) {
        delete mUnloadedChunks[i];
    }
    delete mUnloadedChunks;

    auto end = mChunkList.end();
    for (auto it = mChunkList.begin(); it != end; ++it) {
        delete *it;
    }

    nn::os::FinalizeMutex(&mMutex);
}

LevelChunk* ServerChunkCache::getChunkIfLoaded(int chunkX, int chunkZ) {
    if (inBounds(chunkX, chunkZ)) {
        int idx = computeIdx(chunkX, chunkZ);
        return mChunks[idx];
    }
    return mEmptyChunk;
}

int ServerChunkCache::inBounds(int chunkX, int chunkZ) {
    if (mContainsChunkFunc) {
        return mContainsChunkFunc(qword_c8, chunkX, chunkZ);
    }

    return mDimension->containsChunk(chunkX, chunkZ);
}

int ServerChunkCache::computeIdx(int chunkX, int chunkZ) {
    return (dword_bc + chunkX) * dword_b8 + (dword_bc + chunkZ);
}

LevelChunk* ServerChunkCache::getChunkIfLoadedOrInvalid(int chunkX, int chunkZ) {
    if (inBounds(chunkX, chunkZ)) {
        int idx = computeIdx(chunkX, chunkZ);
        return mChunks[idx];
    }

    return mEmptyChunk;
}

LevelChunk* ServerChunkCache::getChunkIfGenerated(int chunkX, int chunkZ, bool unk) {
    if (!inBounds(chunkX, chunkZ))
        return mEmptyChunk;

    int idx = computeIdx(chunkX, chunkZ);
    LevelChunk* chunk = mChunks[idx];
    LevelChunk* loadedOrInvalid = getChunkIfLoadedOrInvalid(chunkX, chunkZ);

    if (loadedOrInvalid && loadedOrInvalid != mEmptyChunk && !loadedOrInvalid->IsInvalid())
        return loadedOrInvalid;

    EnterCriticalSection(&mMutex);
    PIXBeginNamedEvent(0.0, "Loading chunk");
    LevelChunk* loadedChunk = load(chunkX, chunkZ, loadedOrInvalid);
    PIXEndNamedEvent();

    if (loadedChunk) {
        loadedChunk->load(false);
        LeaveCriticalSection(&mMutex);
        return updateCacheAndPostProcess(chunkX, chunkZ, loadedChunk, chunk, unk);
    }

    LeaveCriticalSection(&mMutex);
    return loadedChunk;
}

// NON_MATCHING: Regswap
LevelChunk* ServerChunkCache::load(int chunkX, int chunkZ, LevelChunk* chunk) {
    LevelChunk* active = chunk;
    if (!mChunkStorage)
        return nullptr;

    if (!chunk) {
        int idx = computeIdx(chunkX, chunkZ);
        active = mUnloadedChunks[idx];
        mUnloadedChunks[idx] = nullptr;
        if (!active || active->IsInvalid()) {
            active = mChunkStorage->load(mLevel, chunkX, chunkZ, active);
            if (!active)
                return nullptr;
        }
    } else if (active->IsInvalid()) {
        active = mChunkStorage->load(mLevel, chunkX, chunkZ, active);
        if (!active)
            return nullptr;
    }

    active->setLastSaveTime(mLevel->getGameTime());

    if (mChunkGenerator)
        mChunkGenerator->recreateLogicStructuresForChunk(active, chunkX, chunkZ);

    return active;
}

// NON_MATCHING: A couple instructions placed in the wrong positions
LevelChunk* ServerChunkCache::updateCacheAndPostProcess(int chunkX, int chunkZ, LevelChunk* newChunk,
                                                        LevelChunk* oldChunk, bool unk) {
    if (!inBounds(chunkX, chunkZ)) {
        return mEmptyChunk;
    }

    int idx = computeIdx(chunkX, chunkZ);

    if (InterlockedCompareExchangeRelease((volatile long*)&mChunks[idx], (long)newChunk, (long)oldChunk)
        == (long)oldChunk) {
        EnterCriticalSection(&mMutex);

        PIXBeginNamedEvent(0.0, "Lighting chunk");
        mChunkGenerator->lightChunk(newChunk);
        PIXEndNamedEvent();

        PIXBeginNamedEvent(0.0, "Post-processing");
        updatePostProcessFlags(chunkX, chunkZ);

        if (newChunk != oldChunk) {
            mChunkList.push_back(newChunk);
        }

        if (unk) {
            if ((newChunk->mPopulatedFlags & 2) == 0 && hasChunk(chunkX + 1, chunkZ + 1)
                && hasChunk(chunkX, chunkZ + 1) && hasChunk(chunkX + 1, chunkZ))
                MinecraftServer::getInstance()->addPostProcessRequest(this, mChunkGenerator, chunkX, chunkZ);
            if (hasChunk(chunkX - 1, chunkZ) && ((getChunk(chunkX - 1, chunkZ)->mPopulatedFlags & 2) == 0)
                && hasChunk(chunkX - 1, chunkZ + 1) && hasChunk(chunkX, chunkZ + 1)
                && hasChunk(chunkX - 1, chunkZ))
                MinecraftServer::getInstance()->addPostProcessRequest(this, mChunkGenerator, chunkX - 1,
                                                                      chunkZ);
            if (hasChunk(chunkX, chunkZ - 1) && ((getChunk(chunkX, chunkZ - 1)->mPopulatedFlags & 2) == 0)
                && hasChunk(chunkX + 1, chunkZ - 1) && hasChunk(chunkX, chunkZ - 1)
                && hasChunk(chunkX + 1, chunkZ))
                MinecraftServer::getInstance()->addPostProcessRequest(this, mChunkGenerator, chunkX,
                                                                      chunkZ - 1);
            if (hasChunk(chunkX - 1, chunkZ - 1)
                && ((getChunk(chunkX - 1, chunkZ - 1)->mPopulatedFlags & 2) == 0)
                && hasChunk(chunkX - 1, chunkZ - 1) && hasChunk(chunkX, chunkZ - 1)
                && hasChunk(chunkX - 1, chunkZ))
                MinecraftServer::getInstance()->addPostProcessRequest(this, mChunkGenerator, chunkX - 1,
                                                                      chunkZ - 1);

            PIXEndNamedEvent();
            LeaveCriticalSection(&mMutex);
            return newChunk;
        }
        newChunk->checkPostProcess(this, mChunkGenerator);
        PIXEndNamedEvent();

        PIXBeginNamedEvent(0.0, "Checking chests");
        if (hasChunk(chunkX - 1, chunkZ) && hasChunk(chunkX - 2, chunkZ) && hasChunk(chunkX - 1, chunkZ + 1)
            && hasChunk(chunkX - 1, chunkZ - 1)) {
            newChunk->checkChests(this, chunkX - 1, chunkZ);
        }
        if (hasChunk(chunkX, chunkZ + 1) && hasChunk(chunkX, chunkZ + 2) && hasChunk(chunkX - 1, chunkZ + 1)
            && hasChunk(chunkX + 1, chunkZ + 1)) {
            newChunk->checkChests(this, chunkX, chunkZ + 1);
        }
        if (hasChunk(chunkX + 1, chunkZ) && hasChunk(chunkX + 2, chunkZ) && hasChunk(chunkX + 1, chunkZ + 1)
            && hasChunk(chunkX + 1, chunkZ - 1)) {
            newChunk->checkChests(this, chunkX + 1, chunkZ);
        }
        if (hasChunk(chunkX, chunkZ - 1) && hasChunk(chunkX, chunkZ - 2) && hasChunk(chunkX - 1, chunkZ - 1)
            && hasChunk(chunkX + 1, chunkZ - 1)) {
            newChunk->checkChests(this, chunkX, chunkZ - 1);
        }
        if (hasChunk(chunkX - 1, chunkZ) && hasChunk(chunkX + 1, chunkZ) && hasChunk(chunkX, chunkZ - 1)
            && hasChunk(chunkX, chunkZ + 1)) {
            newChunk->checkChests(this, chunkX, chunkZ);
        }
        PIXEndNamedEvent();
        LeaveCriticalSection(&mMutex);
    } else {
        if (newChunk) {
            newChunk->unload(true, true);
            delete newChunk;
        }
        return mChunks[idx];
    }
    return newChunk;
}

LevelChunk* ServerChunkCache::getOrCreateChunk(int chunkX, int chunkZ, bool unk) {
    if (!inBounds(chunkX, chunkZ))
        return mEmptyChunk;

    int idx = computeIdx(chunkX, chunkZ);
    LevelChunk* chunk = mChunks[idx];
    LevelChunk* generatedChunk = getChunkIfGenerated(chunkX, chunkZ, unk);
    if (generatedChunk)
        return generatedChunk;

    EnterCriticalSection(&mMutex);
    PIXBeginNamedEvent(0.0, "Creating chunk");
    LevelChunk* newChunk = mChunkGenerator->createChunk(chunkX, chunkZ);
    PIXEndNamedEvent();
    newChunk->load(false);
    LeaveCriticalSection(&mMutex);
    return updateCacheAndPostProcess(chunkX, chunkZ, newChunk, chunk, unk);
}

int ServerChunkCache::getLoadedChunksCount() {
    return mChunkList.size();
}

bool ServerChunkCache::hasChunk(int chunkX, int chunkZ) {
    if (!inBounds(chunkX, chunkZ))
        return true;

    int idx = computeIdx(chunkX, chunkZ);
    LevelChunk* chunk = mChunks[idx];
    if (chunk == nullptr || chunk->IsInvalid())
        return false;

    return true;
}

bool ServerChunkCache::isChunkGeneratedAt(int chunkX, int chunkZ) {
    LevelChunk* chunk = mChunks[computeIdx(chunkX, chunkZ)];

    if (!inBounds(chunkX, chunkZ)) {
        return false;
    }

    if (!chunk) {
        return false;
    }

    return !chunk->isEmpty();
}

std::vector<LevelChunk*>* ServerChunkCache::getLoadedChunkList() {
    return &mChunkList;
}

LevelChunk* ServerChunkCache::create(int chunkX, int chunkZ) {
    return create(chunkX, chunkZ, false);
}

LevelChunk* ServerChunkCache::create(int chunkX, int chunkZ, bool unk) {
    if (!inBounds(chunkX, chunkZ))
        return mEmptyChunk;

    int idx = computeIdx(chunkX, chunkZ);
    LevelChunk* chunk = mChunks[idx];

    if (chunk && chunk->mXPos == chunkX && chunk->mZPos == chunkZ && !chunk->IsInvalid()) {
        return chunk;
    }

    EnterCriticalSection(&mMutex);
    PIXBeginNamedEvent(0.0, "Loading chunk");
    LevelChunk* loadedChunk = load(chunkX, chunkZ, chunk);
    PIXEndNamedEvent();

    if(!loadedChunk && !mChunkGenerator) {
        loadedChunk = mEmptyChunk;
    }
    else if(!loadedChunk && mChunkGenerator) {
        PIXBeginNamedEvent(0.0, "Getting chunk from source");
        loadedChunk = mChunkGenerator->createChunk(chunkX, chunkZ);
        PIXEndNamedEvent();
    }
    
    if(loadedChunk)
        loadedChunk->load(false);

    LeaveCriticalSection(&mMutex);
    return updateCacheAndPostProcess(chunkX, chunkZ, loadedChunk, chunk, unk);
}

void ServerChunkCache::updatePostProcessFlags(int chunkX, int chunkZ) {
    LevelChunk* chunk = getChunk(chunkX, chunkZ);
    if (chunk == mEmptyChunk) {
        flagPostProcessComplete(0, chunkX, chunkZ);
        return;
    }

    // TODO: Lots of magic numbers!
    updatePostProcessFlag(8, chunkX, chunkZ, 0, -1, chunk);
    updatePostProcessFlag(0x10, chunkX, chunkZ, -1, -1, chunk);
    updatePostProcessFlag(4, chunkX, chunkZ, -1, 0, chunk);
    updatePostProcessFlag(0x20, chunkX, chunkZ, -1, 1, chunk);
    updatePostProcessFlag(0x40, chunkX, chunkZ, 0, 1, chunk);
    updatePostProcessFlag(0x80, chunkX, chunkZ, 1, 1, chunk);
    updatePostProcessFlag(0x100, chunkX, chunkZ, 1, 0, chunk);
    updatePostProcessFlag(0x200, chunkX, chunkZ, 1, -1, chunk);

    if ((chunk->mPopulatedFlags & 2)) {
        flagPostProcessComplete(4, chunkX + 1, chunkZ);
        flagPostProcessComplete(0x10, chunkX + 1, chunkZ + 1);
        flagPostProcessComplete(8, chunkX, chunkZ + 1);
        flagPostProcessComplete(0x200, chunkX - 1, chunkZ + 1);
        flagPostProcessComplete(0x100, chunkX - 1, chunkZ);
        flagPostProcessComplete(0x80, chunkX - 1, chunkZ - 1);
        flagPostProcessComplete(0x40, chunkX, chunkZ - 1);
        flagPostProcessComplete(0x20, chunkX + 1, chunkZ - 1);
    }

    flagPostProcessComplete(0, chunkX, chunkZ);
    return;
}

LevelChunk* ServerChunkCache::getChunk(int chunkX, int chunkZ) {
    if (!inBounds(chunkX, chunkZ))
        return mEmptyChunk;

    int idx = computeIdx(chunkX, chunkZ);
    LevelChunk* chunk = mChunks[idx];

    if (chunk && !chunk->IsInvalid())
        return chunk;

    if (mLevel->isFindingSpawn() || byte_28)
        return create(chunkX, chunkZ);

    return mEmptyChunk;
}

LevelChunk* ServerChunkCache::getChunkLoadedOrUnloaded(int chunkX, int chunkZ) {
    if (!inBounds(chunkX, chunkZ))
        return mEmptyChunk;

    int idx = computeIdx(chunkX, chunkZ);
    LevelChunk* chunk = mChunks[idx];

    if (!chunk) {
        chunk = mUnloadedChunks[idx];
    }

    if (chunk && !chunk->IsInvalid()) {
        return chunk;
    }

    if (mLevel->isFindingSpawn() || byte_28)
        return create(chunkX, chunkZ);

    return mEmptyChunk;
}

void ServerChunkCache::updatePostProcessFlag(short flag, int baseX, int baseZ, int offsetX, int offsetZ,
                                             LevelChunk* chunk) {
    int chunkX = baseX + offsetX;
    int chunkZ = baseZ + offsetZ;
    if (hasChunk(chunkX, chunkZ)) {
        LevelChunk* targetChunk = getChunk(chunkX, chunkZ);
        if (targetChunk == mEmptyChunk || (targetChunk->mPopulatedFlags & 2) != 0) {
            chunk->mPopulatedFlags |= flag;
        }
    }
}

void ServerChunkCache::flagPostProcessComplete(short unk, int chunkX, int chunkZ) {
    if (!hasChunk(chunkX, chunkZ))
        return;

    LevelChunk* chunk = mLevel->getChunk(chunkX, chunkZ);
    if (chunk != mEmptyChunk)
        chunk->flagPostProcessComplete(unk);
}

bool ServerChunkCache::saveAllEntities() {
    PIXBeginNamedEvent(0.0, "Save all entities");
    PIXBeginNamedEvent(0.0, "saving to NBT");
    EnterCriticalSection(&mMutex);

    for (auto it = mChunkList.begin(); it != mChunkList.end(); ++it) {
        mChunkStorage->saveEntities(mLevel, *it);
    }

    LeaveCriticalSection(&mMutex);
    PIXEndNamedEvent();

    PIXBeginNamedEvent(0.0, "Flushing");
    mChunkStorage->flush();
    PIXEndNamedEvent();

    PIXEndNamedEvent();
    return true;
}

// ServerChunkCache::save

// ServerChunkCache::tick

bool ServerChunkCache::shouldSave() {
    return mLevel->mShouldSave == false;
}

std::wstring ServerChunkCache::gatherStats() {
    return L"ServerChunkCache: ";
}

std::vector<Biome::MobSpawnerData>* ServerChunkCache::getMobsAt(MobCategory* category, const BlockPos& pos) {
    return mChunkGenerator->getMobsAt(category, pos);
}

void ServerChunkCache::findNearestMapFeature(Level* level, const std::wstring& name, const BlockPos& pos,
                                             bool unk) {
    mChunkGenerator->findNearestMapFeature(level, name, pos, unk);
}

void ServerChunkCache::recreateLogicStructuresForChunk(LevelChunk* chunk, int chunkX, int chunkZ) {}

LevelChunk* ServerChunkCache::getChunkAt(const BlockPos& pos) {
    return getChunk(pos.getX() >> 4, pos.getZ() >> 4);
}

int ServerChunkCache::getLoadedChunks() {
    std::vector<LevelChunk*>* list = getLoadedChunkList();
    return list->size();
}

ChunkSource* ServerChunkCache::getCache() {
    // likely wrong, but other classes require this function to return ChunkSource*
    return (ChunkSource*)mChunks;
}
