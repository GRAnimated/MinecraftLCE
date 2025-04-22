#include "Minecraft.World/level/chunk/ChunkPos.h"
#include "Minecraft.World/level/chunk/LevelChunk.h"
#include "Minecraft.World/phys/BoundingBox.h"
#include "ServerLevel.h"

// NON_MATCHING: Score 840 (lower is better)
std::vector<TickNextTickData*>* ServerLevel::fetchTicksInChunk(LevelChunk* chunk, bool unk) {
    ChunkPos pos = chunk->getPos();
    // NON_MATCHING: 0x710072AAB4
    // fucked math
    int x0 = pos.x * 0x10 - 2;
    int y0 = 0;
    int z0 = pos.z * 0x10 - 2;
    int x1 = pos.x * 0x10 + 0x10;
    int y1 = 256;
    int z1 = pos.z * 0x10 + 0x10;
    BoundingBox bb = BoundingBox(x0, y0, z0, x1, y1, z1);
    return this->fetchTicksInArea(&bb, unk);
}