#pragma once
#include "Minecraft.World/phys/AABB.h"
#include <vector>

class TargetAreaRuleDefinition;
class StringTable;

class LevelRuleset {
protected:
    unsigned char padding[343];
    StringTable* stringTable;

public:
    void getNamedAreas(int type, std::vector<AABB>* vector);
    void getActiveChunkAreas(std::vector<AABB>* vector);
    void getRingsWithinArea(std::vector<TargetAreaRuleDefinition*>* vector, AABB* aabb);
    StringTable* getStringTable();
};
