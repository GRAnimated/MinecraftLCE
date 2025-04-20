//
// Created by DexrnZacAttack on 4/19/2025 (ZPC-I1)
//
#pragma once
#include "Minecraft.World/level/Level.h"

class ServerLevel : public Level {
    std::vector<TickNextTickData*> *fetchTicksInChunk(LevelChunk*, bool) override;
};
