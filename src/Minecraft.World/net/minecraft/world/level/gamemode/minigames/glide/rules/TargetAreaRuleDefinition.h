#pragma once

#include "net/minecraft/world/level/gamemode/minigames/glide/GlideRingGenerator.h"
#include "net/minecraft/world/level/gamemode/rules/NamedAreaRuleDefinition.h"

class TargetAreaRuleDefinition : public NamedAreaRuleDefinition {
public:
    ConsoleGameRules::EGameRuleType getActionType() override;
    const AABB* getBoundingVolume() override;
    void WriteAttributesAsXML(std::string&) override;
    virtual void getPointValue();
    virtual GlideRingGenerator::eGlideRingSize getSize();

    bool isPrimary() { return mPrimary; }

    bool mPrimary;
};
