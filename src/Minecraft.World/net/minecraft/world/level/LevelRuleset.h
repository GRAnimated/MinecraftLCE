#pragma once

#include "net/minecraft/world/phys/AABB.h"
#include <vector>

class TargetAreaRuleDefinition;
class ThermalAreaRuleDefinition;
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
    void getThermalAreas(std::vector<ThermalAreaRuleDefinition*>*);
};
