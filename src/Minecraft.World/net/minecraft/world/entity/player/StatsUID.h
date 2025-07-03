#pragma once

#include "net/minecraft/world/PlayerUID.h"
class StatsUID : public PlayerUID {
public:
    StatsUID();

    static StatsUID EMPTY_SUID();

    int unk;
};
