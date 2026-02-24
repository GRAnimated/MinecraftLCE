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
    m_dwordBc = size / 2;
    m_dwordB8 = size;
    m_xzSize = size;
    m_byte28 = false;

    m_emptyChunk = new EmptyLevelChunk(level, 0, 0);

    m_dimension = level->m_dimension;
    m_level = level;
    m_chunkGenerator = generator;
    m_chunkStorage = storage;

    m_chunks = new LevelChunk*[m_dwordB8 * m_dwordB8];
    memset(m_chunks, 0, m_dwordB8 * m_dwordB8 * sizeof(LevelChunk*));

    m_unloadedChunks = new LevelChunk*[m_dwordB8 * m_dwordB8];
    memset(m_unloadedChunks, 0, m_dwordB8 * m_dwordB8 * sizeof(LevelChunk*));

    m_containsChunkFunc = nullptr;
    m_qwordC8 = nullptr;

    InitializeCriticalSectionAndSpinCount(&m_mutex, 4000);
}

ServerChunkCache::~ServerChunkCache() {
    m_chunkStorage->WaitForAll();

    delete m_chunkStorage;
    delete m_emptyChunk;
    delete m_chunks;
    delete m_chunkGenerator;

    for (int i = 0; i < m_dwordB8 * m_dwordB8; ++i) {
        delete m_unloadedChunks[i];
    }
    delete m_unloadedChunks;

    auto end = m_chunkList.end();
    for (auto it = m_chunkList.begin(); it != end; ++it) {
        delete *it;
    }

    nn::os::FinalizeMutex(&m_mutex);
}

LevelChunk* ServerChunkCache::getChunkIfLoaded(int chunkX, int chunkZ) {
    if (inBounds(chunkX, chunkZ)) {
        int idx = computeIdx(chunkX, chunkZ);
        return m_chunks[idx];
    }
    return m_emptyChunk;
}

int ServerChunkCache::inBounds(int chunkX, int chunkZ) {
    if (m_containsChunkFunc) {
        return m_containsChunkFunc(m_qwordC8, chunkX, chunkZ);
    }

    return m_dimension->containsChunk(chunkX, chunkZ);
}

int ServerChunkCache::computeIdx(int chunkX, int chunkZ) {
    return (m_dwordBc + chunkX) * m_dwordB8 + (m_dwordBc + chunkZ);
}

LevelChunk* ServerChunkCache::getChunkIfLoadedOrInvalid(int chunkX, int chunkZ) {
    if (inBounds(chunkX, chunkZ)) {
        int idx = computeIdx(chunkX, chunkZ);
        return m_chunks[idx];
    }

    return m_emptyChunk;
}

LevelChunk* ServerChunkCache::getChunkIfGenerated(int chunkX, int chunkZ, bool unk) {
    if (!inBounds(chunkX, chunkZ))
        return m_emptyChunk;

    int idx = computeIdx(chunkX, chunkZ);
    LevelChunk* chunk = m_chunks[idx];
    LevelChunk* loadedOrInvalid = getChunkIfLoadedOrInvalid(chunkX, chunkZ);

    if (loadedOrInvalid && loadedOrInvalid != m_emptyChunk && !loadedOrInvalid->IsInvalid())
        return loadedOrInvalid;

    EnterCriticalSection(&m_mutex);
    PIXBeginNamedEvent(0.0, "Loading chunk");
    LevelChunk* loadedChunk = load(chunkX, chunkZ, loadedOrInvalid);
    PIXEndNamedEvent();

    if (loadedChunk) {
        loadedChunk->load(false);
        LeaveCriticalSection(&m_mutex);
        return updateCacheAndPostProcess(chunkX, chunkZ, loadedChunk, chunk, unk);
    }

    LeaveCriticalSection(&m_mutex);
    return loadedChunk;
}

// NON_MATCHING: Regswap
LevelChunk* ServerChunkCache::load(int chunkX, int chunkZ, LevelChunk* chunk) {
    LevelChunk* active = chunk;
    if (!m_chunkStorage)
        return nullptr;

    if (!chunk) {
        int idx = computeIdx(chunkX, chunkZ);
        active = m_unloadedChunks[idx];
        m_unloadedChunks[idx] = nullptr;
        if (!active || active->IsInvalid()) {
            active = m_chunkStorage->load(m_level, chunkX, chunkZ, active);
            if (!active)
                return nullptr;
        }
    } else if (active->IsInvalid()) {
        active = m_chunkStorage->load(m_level, chunkX, chunkZ, active);
        if (!active)
            return nullptr;
    }

    active->setLastSaveTime(m_level->getGameTime());

    if (m_chunkGenerator)
        m_chunkGenerator->recreateLogicStructuresForChunk(active, chunkX, chunkZ);

    return active;
}

// NON_MATCHING: A couple instructions placed in the wrong positions
LevelChunk* ServerChunkCache::updateCacheAndPostProcess(int chunkX, int chunkZ, LevelChunk* newChunk,
                                                        LevelChunk* oldChunk, bool unk) {
    if (!inBounds(chunkX, chunkZ)) {
        return m_emptyChunk;
    }

    int idx = computeIdx(chunkX, chunkZ);

    if (InterlockedCompareExchangeRelease((volatile long*)&m_chunks[idx], (long)newChunk, (long)oldChunk)
        == (long)oldChunk) {
        EnterCriticalSection(&m_mutex);

        PIXBeginNamedEvent(0.0, "Lighting chunk");
        m_chunkGenerator->lightChunk(newChunk);
        PIXEndNamedEvent();

        PIXBeginNamedEvent(0.0, "Post-processing");
        updatePostProcessFlags(chunkX, chunkZ);

        if (newChunk != oldChunk) {
            m_chunkList.push_back(newChunk);
        }

        if (unk) {
            if ((newChunk->m_populatedFlags & 2) == 0 && hasChunk(chunkX + 1, chunkZ + 1)
                && hasChunk(chunkX, chunkZ + 1) && hasChunk(chunkX + 1, chunkZ))
                MinecraftServer::getInstance()->addPostProcessRequest(this, m_chunkGenerator, chunkX, chunkZ);
            if (hasChunk(chunkX - 1, chunkZ) && ((getChunk(chunkX - 1, chunkZ)->m_populatedFlags & 2) == 0)
                && hasChunk(chunkX - 1, chunkZ + 1) && hasChunk(chunkX, chunkZ + 1)
                && hasChunk(chunkX - 1, chunkZ))
                MinecraftServer::getInstance()->addPostProcessRequest(this, m_chunkGenerator, chunkX - 1,
                                                                      chunkZ);
            if (hasChunk(chunkX, chunkZ - 1) && ((getChunk(chunkX, chunkZ - 1)->m_populatedFlags & 2) == 0)
                && hasChunk(chunkX + 1, chunkZ - 1) && hasChunk(chunkX, chunkZ - 1)
                && hasChunk(chunkX + 1, chunkZ))
                MinecraftServer::getInstance()->addPostProcessRequest(this, m_chunkGenerator, chunkX,
                                                                      chunkZ - 1);
            if (hasChunk(chunkX - 1, chunkZ - 1)
                && ((getChunk(chunkX - 1, chunkZ - 1)->m_populatedFlags & 2) == 0)
                && hasChunk(chunkX - 1, chunkZ - 1) && hasChunk(chunkX, chunkZ - 1)
                && hasChunk(chunkX - 1, chunkZ))
                MinecraftServer::getInstance()->addPostProcessRequest(this, m_chunkGenerator, chunkX - 1,
                                                                      chunkZ - 1);

            PIXEndNamedEvent();
            LeaveCriticalSection(&m_mutex);
            return newChunk;
        }
        newChunk->checkPostProcess(this, m_chunkGenerator);
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
        LeaveCriticalSection(&m_mutex);
    } else {
        if (newChunk) {
            newChunk->unload(true, true);
            delete newChunk;
        }
        return m_chunks[idx];
    }
    return newChunk;
}

LevelChunk* ServerChunkCache::getOrCreateChunk(int chunkX, int chunkZ, bool unk) {
    if (!inBounds(chunkX, chunkZ))
        return m_emptyChunk;

    int idx = computeIdx(chunkX, chunkZ);
    LevelChunk* chunk = m_chunks[idx];
    LevelChunk* generatedChunk = getChunkIfGenerated(chunkX, chunkZ, unk);
    if (generatedChunk)
        return generatedChunk;

    EnterCriticalSection(&m_mutex);
    PIXBeginNamedEvent(0.0, "Creating chunk");
    LevelChunk* newChunk = m_chunkGenerator->createChunk(chunkX, chunkZ);
    PIXEndNamedEvent();
    newChunk->load(false);
    LeaveCriticalSection(&m_mutex);
    return updateCacheAndPostProcess(chunkX, chunkZ, newChunk, chunk, unk);
}

int ServerChunkCache::getLoadedChunksCount() {
    return m_chunkList.size();
}

bool ServerChunkCache::hasChunk(int chunkX, int chunkZ) {
    if (!inBounds(chunkX, chunkZ))
        return true;

    int idx = computeIdx(chunkX, chunkZ);
    LevelChunk* chunk = m_chunks[idx];
    if (chunk == nullptr || chunk->IsInvalid())
        return false;

    return true;
}

bool ServerChunkCache::isChunkGeneratedAt(int chunkX, int chunkZ) {
    LevelChunk* chunk = m_chunks[computeIdx(chunkX, chunkZ)];

    if (!inBounds(chunkX, chunkZ)) {
        return false;
    }

    if (!chunk) {
        return false;
    }

    return !chunk->isEmpty();
}

std::vector<LevelChunk*>* ServerChunkCache::getLoadedChunkList() {
    return &m_chunkList;
}

LevelChunk* ServerChunkCache::create(int chunkX, int chunkZ) {
    return create(chunkX, chunkZ, false);
}

LevelChunk* ServerChunkCache::create(int chunkX, int chunkZ, bool unk) {
    if (!inBounds(chunkX, chunkZ))
        return m_emptyChunk;

    int idx = computeIdx(chunkX, chunkZ);
    LevelChunk* chunk = m_chunks[idx];

    if (chunk && chunk->m_xPos == chunkX && chunk->m_zPos == chunkZ && !chunk->IsInvalid()) {
        return chunk;
    }

    EnterCriticalSection(&m_mutex);
    PIXBeginNamedEvent(0.0, "Loading chunk");
    LevelChunk* loadedChunk = load(chunkX, chunkZ, chunk);
    PIXEndNamedEvent();

    if (!loadedChunk && !m_chunkGenerator) {
        loadedChunk = m_emptyChunk;
    } else if (!loadedChunk && m_chunkGenerator) {
        PIXBeginNamedEvent(0.0, "Getting chunk from source");
        loadedChunk = m_chunkGenerator->createChunk(chunkX, chunkZ);
        PIXEndNamedEvent();
    }

    if (loadedChunk)
        loadedChunk->load(false);

    LeaveCriticalSection(&m_mutex);
    return updateCacheAndPostProcess(chunkX, chunkZ, loadedChunk, chunk, unk);
}

void ServerChunkCache::updatePostProcessFlags(int chunkX, int chunkZ) {
    LevelChunk* chunk = getChunk(chunkX, chunkZ);
    if (chunk == m_emptyChunk) {
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

    if ((chunk->m_populatedFlags & 2)) {
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
        return m_emptyChunk;

    int idx = computeIdx(chunkX, chunkZ);
    LevelChunk* chunk = m_chunks[idx];

    if (chunk && !chunk->IsInvalid())
        return chunk;

    if (m_level->isFindingSpawn() || m_byte28)
        return create(chunkX, chunkZ);

    return m_emptyChunk;
}

LevelChunk* ServerChunkCache::getChunkLoadedOrUnloaded(int chunkX, int chunkZ) {
    if (!inBounds(chunkX, chunkZ))
        return m_emptyChunk;

    int idx = computeIdx(chunkX, chunkZ);
    LevelChunk* chunk = m_chunks[idx];

    if (!chunk) {
        chunk = m_unloadedChunks[idx];
    }

    if (chunk && !chunk->IsInvalid()) {
        return chunk;
    }

    if (m_level->isFindingSpawn() || m_byte28)
        return create(chunkX, chunkZ);

    return m_emptyChunk;
}

void ServerChunkCache::updatePostProcessFlag(short flag, int baseX, int baseZ, int offsetX, int offsetZ,
                                             LevelChunk* chunk) {
    int chunkX = baseX + offsetX;
    int chunkZ = baseZ + offsetZ;
    if (hasChunk(chunkX, chunkZ)) {
        LevelChunk* targetChunk = getChunk(chunkX, chunkZ);
        if (targetChunk == m_emptyChunk || (targetChunk->m_populatedFlags & 2) != 0) {
            chunk->m_populatedFlags |= flag;
        }
    }
}

void ServerChunkCache::flagPostProcessComplete(short unk, int chunkX, int chunkZ) {
    if (!hasChunk(chunkX, chunkZ))
        return;

    LevelChunk* chunk = m_level->getChunk(chunkX, chunkZ);
    if (chunk != m_emptyChunk)
        chunk->flagPostProcessComplete(unk);
}

bool ServerChunkCache::saveAllEntities() {
    PIXBeginNamedEvent(0.0, "Save all entities");
    PIXBeginNamedEvent(0.0, "saving to NBT");
    EnterCriticalSection(&m_mutex);

    for (auto it = m_chunkList.begin(); it != m_chunkList.end(); ++it) {
        m_chunkStorage->saveEntities(m_level, *it);
    }

    LeaveCriticalSection(&m_mutex);
    PIXEndNamedEvent();

    PIXBeginNamedEvent(0.0, "Flushing");
    m_chunkStorage->flush();
    PIXEndNamedEvent();

    PIXEndNamedEvent();
    return true;
}

// ServerChunkCache::save

// ServerChunkCache::tick

bool ServerChunkCache::shouldSave() {
    return m_level->m_shouldSave == false;
}

std::wstring ServerChunkCache::gatherStats() {
    return L"ServerChunkCache: ";
}

std::vector<Biome::MobSpawnerData>* ServerChunkCache::getMobsAt(MobCategory* category, const BlockPos& pos) {
    return m_chunkGenerator->getMobsAt(category, pos);
}

void ServerChunkCache::findNearestMapFeature(Level* level, const std::wstring& name, const BlockPos& pos,
                                             bool unk) {
    m_chunkGenerator->findNearestMapFeature(level, name, pos, unk);
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
    return (ChunkSource*)m_chunks;
}
