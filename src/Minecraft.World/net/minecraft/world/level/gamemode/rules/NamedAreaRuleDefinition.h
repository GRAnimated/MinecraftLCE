#pragma once

#include "net/minecraft/world/level/gamemode/rules/GameRuleDefinition.h"

class AABB;
class BlockPos;

class NamedAreaRuleDefinition : public GameRuleDefinition {
public:
    NamedAreaRuleDefinition();

    ~NamedAreaRuleDefinition() override;
    ConsoleGameRules::EGameRuleType getActionType() override;
    const AABB* getBoundingVolume() override;
    void onAttributesAdded() override;
    void WriteAttributesAsXML(std::string&) override;
    virtual bool containsBlock(int, const BlockPos&);

    AABB* getArea();

    std::wstring m_name;
    AABB* m_aabb;
};
