#pragma once
#include "Minecraft.Client/platform/NX/Platform.h"
#include "Minecraft.World/level/Level.h"
#include "Minecraft.World/level/chunk/LevelChunk.h"
#include "Minecraft.World/level/storage/RegionFileCache.h"
#include "Minecraft.World/level/storage/save/ConsoleSaveFileCommon.h"
#include "ChunkStorage.h"
#include "Minecraft.Core/System.h"
#include "Minecraft.Core/io/DataOutputStream.h"
#include <string>

#include <deque>

class DataFixerUpper;

class McRegionChunkStorage : public ChunkStorage {
public:
    McRegionChunkStorage(ConsoleSaveFile* sf, const std::wstring& unk, DataFixerUpper* dfu);
    ~McRegionChunkStorage();
    // params guessed, I assume that's normal around here.
    void load(Level* level, int x, int z, LevelChunk* chunk) override;
    void save(Level* level, LevelChunk* chunk) override;
    // blank on Wii U Edition, probably because of entities.dat not existing.
    // but under Switch, there is a string: "Saving entities..."
    void saveEntities(Level* level, LevelChunk* chunk) override;
    void tick() override;
    // "Flushing entity data..."
    void flush() override;
    // Seems to be inlined McRegionChunkStorage::WaitForAllSaves (in Wii U it's a thunk)
    void WaitForAll() override;
    // Seems to be inlined McRegionChunkStorage::WaitForSaves (in Wii U it's a thunk)
    void WaitIfTooManyQueuedChunks() override;
    void loadEntities(Level* level, LevelChunk* chunk);

    // not sure if this still exists
    // void WaitForAllSaves();
    // same with this
    // void WaitForSaves();

    static std::deque<DataOutputStream*> sDeque;
    static nn::os::MutexType sMutex;

    char unk[8];
    std::wstring unk2;
    ConsoleSaveFileCommon* mSaveFile;
};