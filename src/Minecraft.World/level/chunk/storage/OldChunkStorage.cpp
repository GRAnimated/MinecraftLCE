#include "Minecraft.Client/platform/NX/Platform.h"

#include "Minecraft.World/level/Level.h"

#include "OldChunkStorage.h"

// NON_MATCHING: score 42929
void OldChunkStorage::save(LevelChunk *chunk, Level *lvl, CompoundTag *tag)
{
    lvl->checkSession();
    tag->putShort(L"version", 11);
    tag->putInt(L"xPos", chunk->xPos);
    tag->putInt(L"zPos", chunk->zPos);
    tag->putLong(L"LastUpdate", lvl->getGameTime());
    tag->putLong(L"InhabitedTime", chunk->inhabitedTime);
    // void *blocks = TlsGetValue()
    PIXBeginNamedEvent(0.0, "Getting block data");
    // function here that I don't know the purpose of
    // seems to be inlined everywhere (even sub functions so its impossible to trace back for me)
}
