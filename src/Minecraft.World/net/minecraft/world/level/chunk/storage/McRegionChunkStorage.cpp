#include "Minecraft.Client/platform/NX/Platform.h"
#include "Minecraft.Nbt/CompoundTag.h"
#include "Minecraft.Nbt/NbtIo.h"
#include "Minecraft.World/level/storage/LevelData.h"
#include "McRegionChunkStorage.h"
#include "OldChunkStorage.h"

void McRegionChunkStorage::save(Level* level, LevelChunk* chunk) {
    level->checkSession();
    MemSect(30);
    PIXBeginNamedEvent(0.0, "Getting output stream\n");
    DataOutputStream* chunkOutputStream = RegionFileCache::getChunkDataOutputStream(
        this->mSaveFile, this->unk2, chunk->xPos, chunk->zPos, false);
    PIXEndNamedEvent();

    if (this->mSaveFile->getOriginalSaveVersion() > 7) {
        PIXBeginNamedEvent(0.0, "Writing chunk data");
        OldChunkStorage::save(chunk, level, chunkOutputStream);
        PIXEndNamedEvent();

        PIXBeginNamedEvent(0.0, "Updating chunk queue");

        EnterCriticalSection(&sMutex);
        sDeque.push_back(chunkOutputStream);
        LeaveCriticalSection(&sMutex);

        PIXEndNamedEvent();
    } else {
        EnterCriticalSection(&sMutex);

        PIXBeginNamedEvent(0.0, "Creating tags\n");
        CompoundTag* levelTag = new CompoundTag();
        CompoundTag* tag2 = new CompoundTag();
        levelTag->put(L"Level", tag2);
        OldChunkStorage::save(chunk, level, tag2);
        PIXEndNamedEvent();

        PIXBeginNamedEvent(0.0, "NbtIo writing\n");
        NbtIo::write(levelTag, chunkOutputStream);
        PIXEndNamedEvent();

        LeaveCriticalSection(&sMutex);

        PIXBeginNamedEvent(0.0, "Output closing\n");
        chunkOutputStream->close();
        PIXEndNamedEvent();

        EnterCriticalSection(&sMutex);

        PIXBeginNamedEvent(0.0, "Cleaning up\n");
        chunkOutputStream->deleteChildStream();
        delete chunkOutputStream;
        delete levelTag;

        LeaveCriticalSection(&sMutex);

        PIXEndNamedEvent();
    }

    MemSect(0);
    level->getLevelData()->setSizeOnDisk(this->mSaveFile->getSizeOnDisk());
}
