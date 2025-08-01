#pragma once

#include "net/minecraft/world/level/gamemode/minigames/NamedAreaRuleDefinition.h"
#include "net/minecraft/world/level/gamemode/minigames/glide/GlideRingGenerator.h"

class TargetAreaRuleDefinition : public NamedAreaRuleDefinition {
public:
    int getActionType() override;
    const AABB* getBoundingVolume() override;
    void WriteAttributesAsXML(std::string&) override;
    virtual void getPointValue();
    virtual GlideRingGenerator::eGlideRingSize getSize();

    bool get_90() { return field_90; }

    bool field_90;
};
