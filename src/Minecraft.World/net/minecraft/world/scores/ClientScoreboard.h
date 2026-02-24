#pragma once

#include "net/minecraft/world/scores/Scoreboard.h"
#include "types.h"

class ClientScoreboard : public Scoreboard {
public:
    ClientScoreboard();

    char m_size[0x88 - sizeof(Scoreboard)];
};

ASSERT_SIZEOF(ClientScoreboard, 0x88)
