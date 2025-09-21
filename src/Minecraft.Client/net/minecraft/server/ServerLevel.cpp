#include "ServerLevel.h"

#include "net/minecraft/world/level/chunk/ChunkPos.h"
#include "net/minecraft/world/level/chunk/LevelChunk.h"
#include "net/minecraft/world/level/levelgen/structure/BoundingBox.h"

std::vector<TickNextTickData*>* ServerLevel::fetchTicksInChunk(LevelChunk* chunk, bool unk) {
    ChunkPos chunkPos = chunk->getPos();
    int x0 = (chunkPos.mX << 4) - 2;
    int x1 = x0 + 16 + 2;
    int z0 = (chunkPos.mZ << 4) - 2;
    int z1 = z0 + 16 + 2;
    int y0 = 0;
    int y1 = 256;

    BoundingBox bb = BoundingBox(x0, y0, z0, x1, y1, z1);
    return this->fetchTicksInArea(&bb, unk);
}
