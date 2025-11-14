#include "net/minecraft/world/level/gamemode/rules/NamedAreaRuleDefinition.h"

#include "net/minecraft/core/BlockPos.h"

#include "net/minecraft/core/Vec3i.h"
#include "net/minecraft/world/phys/AABB.h"

NamedAreaRuleDefinition::NamedAreaRuleDefinition() {
    mName = L"";
    mAABB = AABB::newPermanent(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    addStringAttribute(

        ConsoleGameRules::EGameRuleAttr_name, &mName);
    addDoubleAttribute(

        ConsoleGameRules::EGameRuleAttr_x0, &mAABB->minX);
    addDoubleAttribute(

        ConsoleGameRules::EGameRuleAttr_y0, &mAABB->minY);
    addDoubleAttribute(

        ConsoleGameRules::EGameRuleAttr_z0, &mAABB->minZ);
    addDoubleAttribute(

        ConsoleGameRules::EGameRuleAttr_x1, &mAABB->maxX);
    addDoubleAttribute(

        ConsoleGameRules::EGameRuleAttr_y1, &mAABB->maxY);
    addDoubleAttribute(

        ConsoleGameRules::EGameRuleAttr_z1, &mAABB->maxZ);
    addHexAttribute(ConsoleGameRules::EGameRuleAttr_dataTag, &mDataTag);
}

NamedAreaRuleDefinition::~NamedAreaRuleDefinition() {
    delete mAABB;
}

ConsoleGameRules::EGameRuleType NamedAreaRuleDefinition::getActionType() {
    return ConsoleGameRules::EGameRuleType_NamedArea;
}

const AABB* NamedAreaRuleDefinition::getBoundingVolume() {
    return getArea();
}

AABB* NamedAreaRuleDefinition::getArea() {
    return mAABB;
}

void NamedAreaRuleDefinition::onAttributesAdded() {
    mAABB->correctMinMax();
}

void NamedAreaRuleDefinition::WriteAttributesAsXML(std::string& xml) {
    if (!mName.empty())
        WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_name, xml);
    WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_x0, xml);
    WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_y0, xml);
    WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_z0, xml);
    WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_x1, xml);
    WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_y1, xml);
    WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_z1, xml);
    if (mDataTag)
        WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_dataTag, xml);
}

bool NamedAreaRuleDefinition::containsBlock(int i, const BlockPos& blockPos) {
    return (mAABB->minX <= blockPos.getX() && blockPos.getX() <= mAABB->maxX && mAABB->minY <= blockPos.getY()
            && blockPos.getY() <= mAABB->maxY && mAABB->minZ <= blockPos.getZ()
            && blockPos.getZ() <= mAABB->maxZ);
}
