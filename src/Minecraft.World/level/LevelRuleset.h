#pragma once
#include <vector>
#include "Minecraft.World/phys/AABB.h"

class LevelRuleset{
public:
    void getNamedAreas(int type, std::vector<AABB>* vector);
    void getActiveChunkAreas(std::vector<AABB>* vector);
};