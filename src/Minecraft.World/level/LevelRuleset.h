#pragma once
#include "Minecraft.World/phys/AABB.h"
#include <vector>

class StringTable;

class LevelRuleset {
protected:
    unsigned char padding[343];
    StringTable* stringTable;

public:
    void getNamedAreas(int type, std::vector<AABB>* vector);
    void getActiveChunkAreas(std::vector<AABB>* vector);
    StringTable* getStringTable();
};