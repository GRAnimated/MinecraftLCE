#pragma once
#include <vector>
#include <Minecraft.World/phys/AABB.h>

class LevelRuleset{
public:
    void getNamedAreas(int, std::vector<AABB, std::allocator<AABB>>*);
};