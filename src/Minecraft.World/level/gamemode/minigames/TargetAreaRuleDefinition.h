#pragma once

#include "Minecraft.World/level/gamemode/minigames/NamedAreaRuleDefinition.h"
#include "Minecraft.World/level/gamemode/minigames/glide/GlideRingGenerator.h"

class TargetAreaRuleDefinition : public NamedAreaRuleDefinition {
public:
    void getActionType() override;
    void getBoundingVolume() override;
    void WriteAttributesAsXML(std::string&) override;
    virtual void getPointValue();
    virtual GlideRingGenerator::eGlideRingSize getSize();
};
