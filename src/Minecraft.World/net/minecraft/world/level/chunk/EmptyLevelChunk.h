#pragma once

#include "net/minecraft/world/level/chunk/LevelChunk.h"

class EmptyLevelChunk : public LevelChunk {
public:
    EmptyLevelChunk(Level*, int, int);
};
