#pragma once

#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/gamemode/rules/GameRuleDefinition.h"

class LayerGenerator;

class LayerGenerationRuleDefinition : public GameRuleDefinition {
public:
    std::vector<LayerGenerator*>* CreateLayers(Random&, AABB const*, unsigned int, float) const;
};
