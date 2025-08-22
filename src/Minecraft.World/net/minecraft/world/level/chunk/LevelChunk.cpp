#include "net/minecraft/world/level/chunk/LevelChunk.h"

void LevelChunk::staticCtor() {
    InitializeCriticalSection(&LevelChunk::mMutex_710178c150);
    InitializeCriticalSection(&LevelChunk::mMutex_710178c170);
    InitializeCriticalSection(&LevelChunk::mMutex_710178c190);
}

int LevelChunk::getBlockId(int x, int y, int z) {
    return getBlockDataStorage(y)->get(x, y % 128, z);
}

bool LevelChunk::isTerrainPopulated() {
    return unkIsInhabited >> 2 & 1; //
}

void LevelChunk::writeCompressedDataData(DataOutputStream* out) {
    mDataDataLower->write(out);
    mDataDataUpper->write(out);
}

void LevelChunk::writeCompressedBlockData(DataOutputStream* out) {
    mBlockDataLower->write(out);
    mBlockDataUpper->write(out);
}

void LevelChunk::writeCompressedSkyLightData(DataOutputStream* out) {
    mSkyLightDataLower->write(out);
    mSkyLightDataUpper->write(out);
}

void LevelChunk::writeCompressedBlockLightData(DataOutputStream* out) {
    mBlockLightDataLower->write(out);
    mBlockLightDataUpper->write(out);
}

ChunkPos LevelChunk::getPos() {
    return ChunkPos(this->xPos, this->zPos);
}
