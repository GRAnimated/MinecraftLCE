#pragma once

#include "net/minecraft/world/level/Level.h"
#include "types.h"

class ServerLevel : public Level {
public:
    std::vector<TickNextTickData*>* fetchTicksInChunk(LevelChunk*, bool) override;

    static void staticCtor();

    void* m_size[27];
    int m_field388;
    bool m_field38C;
    bool m_shouldSave;
    void* m_size2[43];
};

static_assert(sizeof(ServerLevel));

ASSERT_SIZEOF(ServerLevel, 0x4E8)
