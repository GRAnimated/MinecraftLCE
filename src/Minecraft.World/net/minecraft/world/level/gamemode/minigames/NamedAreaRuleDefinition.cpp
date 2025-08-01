#include "net/minecraft/world/level/gamemode/minigames/NamedAreaRuleDefinition.h"

#include "net/minecraft/core/BlockPos.h"

#include "net/minecraft/core/Vec3i.h"
#include "net/minecraft/world/phys/AABB.h"

NamedAreaRuleDefinition::NamedAreaRuleDefinition() {
    mName = L"";
    mAABB = AABB::newPermanent(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    addStringAttribute(

        ConsoleGameRules::EGameRuleAttr_slot, &mName);
    addDoubleAttribute(

        ConsoleGameRules::EGameRuleAttr_x, &mAABB->min.x);
    addDoubleAttribute(

        ConsoleGameRules::EGameRuleAttr_y, &mAABB->min.y);
    addDoubleAttribute(

        ConsoleGameRules::EGameRuleAttr_z, &mAABB->min.z);
    addDoubleAttribute(

        ConsoleGameRules::EGameRuleAttr_x0, &mAABB->max.x);
    addDoubleAttribute(

        ConsoleGameRules::EGameRuleAttr_y0, &mAABB->max.y);
    addDoubleAttribute(

        ConsoleGameRules::EGameRuleAttr_z0, &mAABB->max.z);
    addHexAttribute(ConsoleGameRules::EGameRuleAttr_promptName, &dword_40);
}

NamedAreaRuleDefinition::~NamedAreaRuleDefinition() {
    delete mAABB;
}

int NamedAreaRuleDefinition::getActionType() {
    return 17;
}

const AABB* NamedAreaRuleDefinition::getBoundingVolume() {
    return getArea();
}

const AABB* NamedAreaRuleDefinition::getArea() {
    return mAABB;
}

void NamedAreaRuleDefinition::onAttributesAdded() {
    mAABB->correctMinMax();
}

void NamedAreaRuleDefinition::WriteAttributesAsXML(std::string& xml) {
    if (!mName.empty())
        WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_slot, xml);
    WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_x, xml);
    WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_y, xml);
    WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_z, xml);
    WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_x0, xml);
    WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_y0, xml);
    WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_z0, xml);
    if (dword_40)
        WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_promptName, xml);
}

bool NamedAreaRuleDefinition::containsBlock(int i, const BlockPos& blockPos) {
    return (mAABB->min.x <= blockPos.getX() && blockPos.getX() <= mAABB->max.x
            && mAABB->min.y <= blockPos.getY() && blockPos.getY() <= mAABB->max.y
            && mAABB->min.z <= blockPos.getZ() && blockPos.getZ() <= mAABB->max.z);
}
