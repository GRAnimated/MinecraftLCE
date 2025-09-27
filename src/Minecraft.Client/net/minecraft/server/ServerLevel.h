#pragma once

#include "net/minecraft/world/level/Level.h"

class ServerLevel : public Level {
public:
    std::vector<TickNextTickData*>* fetchTicksInChunk(LevelChunk*, bool) override;

    static void staticCtor();
};
