#pragma once

#include "net/minecraft/world/level/gamemode/rules/NamedAreaRuleDefinition.h"

class ThermalAreaRuleDefinition : public NamedAreaRuleDefinition {
public:
    static const wchar_t* DIRECTION_NAMES[8];

    enum eDirection {
        DIRECTION_UNDEFINED = -1,
        DIRECTION_PLUS_X = 0,
        DIRECTION_MINUS_X = 1,
        DIRECTION_PLUS_Z = 2,
        DIRECTION_MINUS_Z = 3,
        DIRECTION_OMNI_PLUS_X = 4,
        DIRECTION_OMNI_MINUS_X = 5,
        DIRECTION_OMNI_PLUS_Z = 6,
        DIRECTION_OMNI_MINUS_Z = 7
    };

    ThermalAreaRuleDefinition();

    ConsoleGameRules::EGameRuleType getActionType() override;
    void addAttribute(const std::wstring&, const std::wstring&) override;
    void WriteAttributesAsXML(std::string&) override;

    bool getConditionsMet(std::shared_ptr<Entity>);
    void resetConditions();
    void updateUseCount();
    bool setBoostMods(int&, int&);
    int getBoostDirection();

    double getLiftForceModifier() const {
        if (m_isActive)
            return m_liftForceModifier;
        return 1.0;
    }

    double getSpeedBoost() const {
        if (m_isActive)
            return m_speedBoost;
        return 0.0;
    }

    double getStaticLift() const {
        if (m_isActive)
            return m_staticLift;
        return 0.0;
    }

    double getTargetHeight() const {
        if (m_isActive)
            return m_targetHeight;
        return 0.0;
    }

    bool isActive() const { return m_isActive; }

    double m_liftForceModifier;
    double m_staticLift;
    double m_targetHeight;
    double m_speedBoost;
    eDirection m_boostDirection;
    int m_conditionType;
    int m_conditionValue0;
    int m_conditionValue1;
    bool m_isActive;
    int m_dwordC4;
};
