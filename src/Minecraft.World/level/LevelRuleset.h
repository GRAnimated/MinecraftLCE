#pragma once
#include "Minecraft.World/phys/AABB.h"
#include <vector>

class LevelRuleset {
public:
    void getNamedAreas(int type, std::vector<AABB>* vector);
    void getActiveChunkAreas(std::vector<AABB>* vector);
};