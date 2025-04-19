#include "Minecraft.Client/platform/NX/Platform.h"
#include "Minecraft.Nbt/CompoundTag.h"
#include "McRegionChunkStorage.h"
#include "OldChunkStorage.h"
#include "Minecraft.Nbt/NbtIo.h"

// NON-MATCHING
void McRegionChunkStorage::save(Level* level, LevelChunk* chunk)
{
    level->checkSession();
    MemSect(30);
    PIXBeginNamedEvent(0.0, "Getting output stream\n");
    DataOutputStream *cOutputStream = RegionFileCache::getChunkDataOutputStream(this->mSaveFile, this->unk2, chunk->x, chunk->z, false);
    PIXEndNamedEvent();
    if (true /* call vfunc this->mSaveFile + 168() */) {
        EnterCriticalSection(sMutex);
        PIXBeginNamedEvent(0.0, "Creating tags\n");
        CompoundTag *levelTag = new CompoundTag();
        CompoundTag *tag2 = new CompoundTag();
        levelTag->put(L"Level", tag2);
        OldChunkStorage::save(chunk, level, tag2);
        PIXEndNamedEvent();

        PIXBeginNamedEvent(0.0, "NbtIo writing\n");
        DataOutput *unk;
        if (cOutputStream) {
            // unk = cOutputStream + 8; // sets to DataOutput
        } else {
            unk = nullptr;
        }
        NbtIo::write(levelTag, unk);
        PIXEndNamedEvent();

        LeaveCriticalSection(sMutex);

        PIXBeginNamedEvent(0.0, "Output closing\n");
        cOutputStream->close();
        PIXEndNamedEvent();

        EnterCriticalSection(sMutex);
        PIXBeginNamedEvent(0.0, "Cleaning up\n");
        cOutputStream->deleteChildStream();
        if (cOutputStream) delete cOutputStream; // guessed
        if (levelTag) delete levelTag; // guessed
        LeaveCriticalSection(sMutex);
        PIXEndNamedEvent();
    } else {
        PIXBeginNamedEvent(0.0, "Writing chunk data");
        OldChunkStorage::save(chunk, level, cOutputStream);
        PIXEndNamedEvent();

        PIXBeginNamedEvent(0.0, "Updating chunk queue");
        // std::deque::push_back
        LeaveCriticalSection(sMutex);
        PIXEndNamedEvent();
    }
    MemSect(0);
    LevelData *levelData = level->getLevelData();
    // unsigned long size = this->mSaveFile->104() // call another vfunc on ConsoleSaveFile (to get the size)
    // levelData->setSizeOnDisk(size);
}
