#include "ServerLevel.h"

#include "Minecraft.World/level/chunk/ChunkPos.h"
#include "Minecraft.World/level/chunk/LevelChunk.h"
#include "Minecraft.World/phys/BoundingBox.h"

std::vector<TickNextTickData*>* ServerLevel::fetchTicksInChunk(LevelChunk* chunk, bool unk) {
    ChunkPos chunkPos = chunk->getPos();
    int x0 = (chunkPos.x << 4) - 2;
    int x1 = x0 + 16 + 2;
    int z0 = (chunkPos.z << 4) - 2;
    int z1 = z0 + 16 + 2;
    int y0 = 0;
    int y1 = 256;

    BoundingBox bb = BoundingBox(x0, y0, z0, x1, y1, z1);
    return this->fetchTicksInArea(&bb, unk);
}
