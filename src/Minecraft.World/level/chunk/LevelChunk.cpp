#include "Minecraft.World/level/chunk/LevelChunk.h"

void LevelChunk::writeCompressedDataData(DataOutputStream* out) {
    dataData1->write(out);
    dataData2->write(out);
}

void LevelChunk::writeCompressedBlockData(DataOutputStream* out) {
    blockData1->write(out);
    blockData2->write(out);
}

void LevelChunk::writeCompressedSkyLightData(DataOutputStream* out) {
    skyLightData1->write(out);
    skyLightData2->write(out);
}

void LevelChunk::writeCompressedBlockLightData(DataOutputStream* out) {
    blockLightData1->write(out);
    blockLightData2->write(out);
}

ChunkPos LevelChunk::getPos() {
    return ChunkPos(this->xPos, this->zPos);
}