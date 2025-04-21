#include "Minecraft.World/level/chunk/LevelChunk.h"

ChunkPos LevelChunk::getPos() {
    return ChunkPos(this->xPos, this->zPos);
}