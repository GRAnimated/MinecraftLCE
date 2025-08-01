#pragma once

#include "net/minecraft/world/level/gamemode/minigames/GameRuleDefinition.h"

class AABB;
class BlockPos;

class NamedAreaRuleDefinition : public GameRuleDefinition {
public:
    NamedAreaRuleDefinition();

    ~NamedAreaRuleDefinition() override;
    int getActionType() override;
    const AABB* getBoundingVolume() override;
    void onAttributesAdded() override;
    void WriteAttributesAsXML(std::string&) override;
    virtual bool containsBlock(int, const BlockPos&);

    const AABB* getArea();

    std::wstring mName;
    AABB* mAABB;
};
