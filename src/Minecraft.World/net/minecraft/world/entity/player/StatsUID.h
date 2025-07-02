#pragma once

#include "Minecraft.World/PlayerUID.h"
class StatsUID : public PlayerUID {
public:
    StatsUID();

    static StatsUID EMPTY_SUID();

    int unk;
};