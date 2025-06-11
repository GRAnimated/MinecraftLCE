#pragma once

#include "types.h"
#include "Minecraft.World/scores/Scoreboard.h"

class ClientScoreboard : public Scoreboard {
public:
    ClientScoreboard();

    char size[0x88 - sizeof(Scoreboard)];
};

ASSERT_SIZEOF(ClientScoreboard, 0x88)
