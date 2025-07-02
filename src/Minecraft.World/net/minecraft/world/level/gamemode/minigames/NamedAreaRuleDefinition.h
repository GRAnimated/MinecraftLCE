#pragma once

#include "Minecraft.World/level/gamemode/minigames/GameRuleDefinition.h"

class AABB;
class BlockPos;

class NamedAreaRuleDefinition : public GameRuleDefinition {
public:
    void getActionType() override;
    void getBoundingVolume() override;
    void onAttributesAdded() override;
    void WriteAttributesAsXML(std::string&) override;
    virtual void containsBlock(int, const BlockPos&);

    const AABB* getArea();
};
