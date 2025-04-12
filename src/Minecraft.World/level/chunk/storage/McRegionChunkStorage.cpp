#include "McRegionChunkStorage.h"

McRegionChunkStorage::McRegionChunkStorage(ConsoleSaveFile* sf, const std::wstring& unk,
                                           DataFixerUpper* dfu) {}

McRegionChunkStorage::~McRegionChunkStorage() {}

void McRegionChunkStorage::load(Level* level, int x, int z, LevelChunk* chunk) {}

void McRegionChunkStorage::save(Level* level, LevelChunk* chunk) {}

void McRegionChunkStorage::saveEntities(Level* level, LevelChunk* chunk) {}

void McRegionChunkStorage::tick() {}

void McRegionChunkStorage::flush() {}

void McRegionChunkStorage::WaitForAll() {}

void McRegionChunkStorage::WaitIfTooManyQueuedChunks() {}

void McRegionChunkStorage::loadEntities(Level* level, LevelChunk* chunk) {}
