#include "Minecraft.World/level/chunk/ChunkSource.h"

void ChunkSource::flagPostProcessComplete(short, int, int) {}

bool ChunkSource::isChunkGeneratedAt(int, int) {
    return false;
}

bool ChunkSource::reallyHasChunk(int x, int z) {
    return hasChunk(x, z);
}

LevelChunk* ChunkSource::getChunkLoadedOrUnloaded(int x, int z) {
    return getChunk(x, z);
}

void ChunkSource::lightChunk(LevelChunk*) {}

bool ChunkSource::saveAllEntities() {
    return false;
}

ChunkSource* ChunkSource::getCache() {
    return nullptr;
}

void ChunkSource::dataReceived(int, int) {}
