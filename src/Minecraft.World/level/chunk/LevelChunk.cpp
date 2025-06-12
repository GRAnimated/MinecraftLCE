#include "Minecraft.World/level/chunk/LevelChunk.h"

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