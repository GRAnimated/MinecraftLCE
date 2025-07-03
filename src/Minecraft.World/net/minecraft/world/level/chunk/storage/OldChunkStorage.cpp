#include "OldChunkStorage.h"

#include "NX/Platform.h"

#include "com/mojang/nbt/ListTag.h"
#include "com/mojang/nbt/NbtIo.h"

#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/entity/BlockEntity.h"
#include "net/minecraft/world/level/tick/TickNextTickData.h"

// NON_MATCHING | Score: 42929 (lower is better)
void OldChunkStorage::save(LevelChunk* chunk, Level* lvl, CompoundTag* tag) {
    lvl->checkSession();
    tag->putShort(L"version", CHUNK_VERSION);
    tag->putInt(L"xPos", chunk->xPos);
    tag->putInt(L"zPos", chunk->zPos);
    tag->putLong(L"LastUpdate", lvl->getGameTime());
    tag->putLong(L"InhabitedTime", chunk->inhabitedTime);
    // void *blocks = TlsGetValue()
    PIXBeginNamedEvent(0.0, "Getting block data");
    // function here that I don't know the purpose of
    // seems to be inlined everywhere (even sub functions so its impossible to trace back for me)
}

// NON_MATCHING | Score: 7824 (lower is better)
void OldChunkStorage::save(LevelChunk* chunk, Level* lvl, DataOutputStream* out) {
    // write header
    out->writeShort(CHUNK_VERSION);        // chunk ver
    out->writeInt(chunk->xPos);            // chunk x pos
    out->writeInt(chunk->zPos);            // chunk z pos
    out->writeLong(lvl->getGameTime());    // lastModified (write current in-game time)
    out->writeLong(chunk->inhabitedTime);  // inhabitedTime

    // write blocks
    PIXBeginNamedEvent(0.0, "Getting block data");
    chunk->writeCompressedBlockData(out);
    PIXEndNamedEvent();

    // write "data"
    // I put some data in your data so you can data while you data
    PIXBeginNamedEvent(0.0, "Getting data data");
    chunk->writeCompressedDataData(out);
    PIXEndNamedEvent();

    // write light data
    PIXBeginNamedEvent(0.0, "Getting sky and block light data");
    chunk->writeCompressedSkyLightData(out);
    chunk->writeCompressedBlockLightData(out);
    PIXEndNamedEvent();

    // write heightmap
    out->write(chunk->getHeightmap());

    // write biomes
    out->writeShort(chunk->biomeCount);
    out->write(chunk->getBiomes());

    // write entities
    PIXBeginNamedEvent(0.0, "Saving entities");
    CompoundTag* tileEntities = new CompoundTag();
    // saveEntities is meant to be called but was moved to entities.dat
    PIXBeginNamedEvent(0.0, "Saving block entities");
    ListTag* tileEntitiesList = new ListTag();
    // NON_MATCHING | At 0x71002326BC
    // Weird for loop
    // love resharper unknown type
    for (std::pair<const BlockPos, std::shared_ptr<BlockEntity>>& entity : *chunk->blockEntities) {
        CompoundTag* tileEntity = new CompoundTag();
        entity.second->save(tileEntity);  // guessed
        tileEntitiesList->add(tileEntity);
    }

    tileEntities->put(L"TileEntities", tileEntitiesList);
    PIXEndNamedEvent();
    PIXBeginNamedEvent(0.0, "Saving block tick data");
    std::vector<TickNextTickData*>* ticks = lvl->fetchTicksInChunk(chunk, false);
    if (ticks) {
        int saveTime = lvl->getGameTime();
        ListTag* ticksList = new ListTag(0);
        // NON_MATCHING | At 0x710023296c
        // weird bullshit go (weird ass for loop, I sure love myself some while ( v22 < 0xAAAAAAAAAAAAAAABLL *
        // ((__int64)(v20[1] - *v20) >> 4) ))
        for (TickNextTickData* tick : *ticks) {
            CompoundTag* tickTag = new CompoundTag();
            tickTag->putInt(L"i", tick->block->getId());
            tickTag->putInt(L"x", tick->pos->getX());
            tickTag->putInt(L"y", tick->pos->getY());
            tickTag->putInt(L"z", tick->pos->getZ());
            tickTag->putInt(L"t", saveTime);  // something - saveTime
            ticksList->add(tickTag);
        }
        tileEntities->put(L"TileTicks", ticksList);
        delete ticks;
    }
    PIXEndNamedEvent();

    NbtIo::write(tileEntities, out);
    delete tileEntities;
    PIXEndNamedEvent();
}
