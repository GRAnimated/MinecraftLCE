#include "net/minecraft/world/level/gamemode/rules/NamedAreaRuleDefinition.h"

#include "net/minecraft/core/BlockPos.h"

#include "net/minecraft/core/Vec3i.h"
#include "net/minecraft/world/phys/AABB.h"

NamedAreaRuleDefinition::NamedAreaRuleDefinition() {
    m_name = L"";
    m_aabb = AABB::newPermanent(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    addStringAttribute(

        ConsoleGameRules::EGameRuleAttr_name, &m_name);
    addDoubleAttribute(

        ConsoleGameRules::EGameRuleAttr_x0, &m_aabb->m_inX);
    addDoubleAttribute(

        ConsoleGameRules::EGameRuleAttr_y0, &m_aabb->m_inY);
    addDoubleAttribute(

        ConsoleGameRules::EGameRuleAttr_z0, &m_aabb->m_inZ);
    addDoubleAttribute(

        ConsoleGameRules::EGameRuleAttr_x1, &m_aabb->m_axX);
    addDoubleAttribute(

        ConsoleGameRules::EGameRuleAttr_y1, &m_aabb->m_axY);
    addDoubleAttribute(

        ConsoleGameRules::EGameRuleAttr_z1, &m_aabb->m_axZ);
    addHexAttribute(ConsoleGameRules::EGameRuleAttr_dataTag, &m_dataTag);
}

NamedAreaRuleDefinition::~NamedAreaRuleDefinition() {
    delete m_aabb;
}

ConsoleGameRules::EGameRuleType NamedAreaRuleDefinition::getActionType() {
    return ConsoleGameRules::EGameRuleType_NamedArea;
}

const AABB* NamedAreaRuleDefinition::getBoundingVolume() {
    return getArea();
}

AABB* NamedAreaRuleDefinition::getArea() {
    return m_aabb;
}

void NamedAreaRuleDefinition::onAttributesAdded() {
    m_aabb->correctMinMax();
}

void NamedAreaRuleDefinition::WriteAttributesAsXML(std::string& xml) {
    if (!m_name.empty())
        WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_name, xml);
    WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_x0, xml);
    WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_y0, xml);
    WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_z0, xml);
    WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_x1, xml);
    WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_y1, xml);
    WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_z1, xml);
    if (m_dataTag)
        WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_dataTag, xml);
}

bool NamedAreaRuleDefinition::containsBlock(int i, const BlockPos& blockPos) {
    return (m_aabb->m_inX <= blockPos.getX() && blockPos.getX() <= m_aabb->m_axX
            && m_aabb->m_inY <= blockPos.getY() && blockPos.getY() <= m_aabb->m_axY
            && m_aabb->m_inZ <= blockPos.getZ() && blockPos.getZ() <= m_aabb->m_axZ);
}
