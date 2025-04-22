#pragma once
#include "Minecraft.World/level/Level.h"

class ServerLevel : public Level {
    std::vector<TickNextTickData*>* fetchTicksInChunk(LevelChunk*, bool) override;
};
