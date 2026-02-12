#include "net/minecraft/world/level/chunk/LevelChunk.h"

#include "net/minecraft/world/level/block/Block.h"

void LevelChunk::staticCtor() {
    InitializeCriticalSection(&LevelChunk::mMutex_710178c150);
    InitializeCriticalSection(&LevelChunk::mMutex_710178c170);
    InitializeCriticalSection(&LevelChunk::mMutex_710178c190);
}

void LevelChunk::writeCompressedDataData(DataOutputStream* out) {
    m_dataDataLower->write(out);
    m_dataDataUpper->write(out);
}

void LevelChunk::writeCompressedBlockData(DataOutputStream* out) {
    m_blockDataLower->write(out);
    m_blockDataUpper->write(out);
}

void LevelChunk::writeCompressedSkyLightData(DataOutputStream* out) {
    m_skyLightDataLower->write(out);
    m_skyLightDataUpper->write(out);
}

void LevelChunk::writeCompressedBlockLightData(DataOutputStream* out) {
    m_blockLightDataLower->write(out);
    m_blockLightDataUpper->write(out);
}

ChunkPos LevelChunk::getPos() {
    return ChunkPos(this->m_xPos, this->m_zPos);
}

Block* LevelChunk::GetBlock(CompressedBlockStorage* storage, int x, int y, int z) {
    const int y0 = y < 0 ? y + 127 : y;
    return Block::byId(storage->get(x, y - (y0 & 0xFFFFFF80), z) & 0xFF);
}
