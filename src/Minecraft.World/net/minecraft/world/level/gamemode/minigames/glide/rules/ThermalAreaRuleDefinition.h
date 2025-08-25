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
        if (mIsActive)
            return mLiftForceModifier;
        return 1.0;
    }

    double getSpeedBoost() const {
        if (mIsActive)
            return mSpeedBoost;
        return 0.0;
    }

    double getStaticLift() const {
        if (mIsActive)
            return mStaticLift;
        return 0.0;
    }

    double getTargetHeight() const {
        if (mIsActive)
            return mTargetHeight;
        return 0.0;
    }

    bool isActive() const { return mIsActive; }

    double mLiftForceModifier;
    double mStaticLift;
    double mTargetHeight;
    double mSpeedBoost;
    eDirection mBoostDirection;
    int mConditionType;
    int mConditionValue0;
    int mConditionValue1;
    bool mIsActive;
    int dword_c4;
};
