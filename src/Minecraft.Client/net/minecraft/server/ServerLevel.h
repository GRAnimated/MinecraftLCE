#pragma once

#include "net/minecraft/world/level/Level.h"
#include "types.h"

class ServerLevel : public Level {
public:
    std::vector<TickNextTickData*>* fetchTicksInChunk(LevelChunk*, bool) override;

    static void staticCtor();

    void* size[27];
    int field_388;
    bool field_38C;
    bool mShouldSave;
    void* size2[43];
};

static_assert(sizeof(ServerLevel));

ASSERT_SIZEOF(ServerLevel, 0x4E8)
