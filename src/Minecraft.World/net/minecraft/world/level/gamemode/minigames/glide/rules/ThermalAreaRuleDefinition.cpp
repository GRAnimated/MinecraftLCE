#include "net/minecraft/world/level/gamemode/minigames/glide/rules/ThermalAreaRuleDefinition.h"

#include "java/io/File.h"
#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/client/multiplayer/MultiPlayerLevel.h"
#include "net/minecraft/world/entity/Entity.h"
#include "net/minecraft/world/entity/player/Player.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/scores/ClientScoreboard.h"

const wchar_t* ThermalAreaRuleDefinition::DIRECTION_NAMES[8] = {
    L"plus_x",      L"minus_x",      L"plus_z",      L"minus_z",
    L"omni_plus_x", L"omni_minus_x", L"omni_plus_z", L"omni_minus_z",
};

ThermalAreaRuleDefinition::ThermalAreaRuleDefinition() {
    m_liftForceModifier = 1.0;
    m_staticLift = 0.0;
    m_targetHeight = 0.0;
    m_speedBoost = 0.0;
    m_isActive = true;
    m_boostDirection = DIRECTION_OMNI_PLUS_X;
    m_conditionType = DIRECTION_PLUS_X;
    m_conditionValue0 = 0;
    m_conditionValue1 = 0;
    GameRuleDefinition::addDoubleAttribute((ConsoleGameRules::EGameRuleAttr_liftForceModifier),
                                           &m_liftForceModifier);
    GameRuleDefinition::addDoubleAttribute(ConsoleGameRules::EGameRuleAttr_staticLift, &m_staticLift);
    GameRuleDefinition::addDoubleAttribute(ConsoleGameRules::EGameRuleAttr_targetHeight, &m_targetHeight);
    GameRuleDefinition::addDoubleAttribute(ConsoleGameRules::EGameRuleAttr_speedBoost, &m_speedBoost);
    GameRuleDefinition::addIntAttribute(ConsoleGameRules::EGameRuleAttr_condition_type, &m_conditionType);
    GameRuleDefinition::addIntAttribute(ConsoleGameRules::EGameRuleAttr_condition_value_0,
                                        &m_conditionValue0);
    GameRuleDefinition::addIntAttribute(ConsoleGameRules::EGameRuleAttr_condition_value_1,
                                        &m_conditionValue1);
    m_dwordC4 = 0;
}

ConsoleGameRules::EGameRuleType ThermalAreaRuleDefinition::getActionType() {
    return ConsoleGameRules::EGameRuleType_ThermalArea;
}

void ThermalAreaRuleDefinition::addAttribute(const std::wstring& name, const std::wstring& value) {
    if (name.compare(IGameRuleAttribute::ATTRIBUTE_NAMES[84]) != 0) {
        GameRuleDefinition::addAttribute(name, value);
        return;
    }

    int direction = DIRECTION_UNDEFINED;
    for (int i = 0; i < 8; ++i) {
        if (value.compare(DIRECTION_NAMES[i]) == 0) {
            direction = i;
            break;
        }
    }

    if (direction != DIRECTION_UNDEFINED) {
        m_boostDirection = (eDirection)direction;
    }
}

void ThermalAreaRuleDefinition::WriteAttributesAsXML(std::string& xml) {
    if (!m_name.empty())
        GameRuleDefinition::WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_name, xml);

    if (m_liftForceModifier != 1.0)
        GameRuleDefinition::WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_liftForceModifier, xml);

    if (m_staticLift != 0.0)
        GameRuleDefinition::WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_staticLift, xml);

    if (m_targetHeight != 0.0)
        GameRuleDefinition::WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_targetHeight, xml);

    if (m_speedBoost != 0.0) {
        GameRuleDefinition::WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_speedBoost, xml);
        std::string str
            = formatstr(" boostDirection=\"%ls\"",
                        ThermalAreaRuleDefinition::DIRECTION_NAMES[(unsigned int)m_boostDirection]);
        xml.append(str);
    }

    if (m_conditionType) {
        GameRuleDefinition::WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_condition_type, xml);
        GameRuleDefinition::WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_condition_value_0, xml);
        GameRuleDefinition::WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_condition_value_1, xml);
    }

    GameRuleDefinition::WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_x0, xml);
    GameRuleDefinition::WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_y0, xml);
    GameRuleDefinition::WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_z0, xml);
    GameRuleDefinition::WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_x1, xml);
    GameRuleDefinition::WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_y1, xml);
    GameRuleDefinition::WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_z1, xml);

    if (m_dataTag)
        GameRuleDefinition::WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_dataTag, xml);
}

// NON_MATCHING: The branch for the first return true gets optimized
bool ThermalAreaRuleDefinition::getConditionsMet(std::shared_ptr<Entity> entity) {
    if (m_conditionType == 0)
        return true;

    if (m_conditionType == 1) {
        if (m_dwordC4 >= m_conditionValue0)
            return false;
        return true;
    }

    if (m_conditionType == 2) {
        if (entity->isType(ePlayer)) {
            MultiPlayerLevel* level = (MultiPlayerLevel*)(Minecraft::GetInstance()->m_level);
            ClientScoreboard* scoreboard = level->GetClientScoreboard();
            std::shared_ptr<Player> player = std::static_pointer_cast<Player>(entity);

            int lapsCompleted = scoreboard->GetLapsCompleted(player->getSUID(), -1);
            if (lapsCompleted < m_conditionValue0 || lapsCompleted > m_conditionValue1)
                return false;
        }
    }

    return true;
}

void ThermalAreaRuleDefinition::resetConditions() {
    m_dwordC4 = 0;
}

void ThermalAreaRuleDefinition::updateUseCount() {
    ++m_dwordC4;
}

const int cDirectionX[4] = {1, -1, 0, 0};
const int cDirectionZ[4] = {0, 0, 1, -1};

bool ThermalAreaRuleDefinition::setBoostMods(int& xMultiplier, int& zMultiplier) {
    int dir = m_boostDirection;

    if (dir < (unsigned int)4) {
        xMultiplier = cDirectionX[dir];
        zMultiplier = cDirectionZ[dir];
        return true;
    }

    return false;
}

int ThermalAreaRuleDefinition::getBoostDirection() {
    return m_boostDirection;
}
