#pragma once

#include "net/minecraft/world/level/Level.h"

class ServerLevel : public Level {
    std::vector<TickNextTickData*>* fetchTicksInChunk(LevelChunk*, bool) override;
};
