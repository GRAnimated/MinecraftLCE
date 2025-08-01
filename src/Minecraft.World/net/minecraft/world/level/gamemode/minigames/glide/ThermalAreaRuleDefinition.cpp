#include "net/minecraft/world/level/gamemode/minigames/glide/ThermalAreaRuleDefinition.h"

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
    mLaps = 1.0;
    mLiftForceModifier = 0.0;
    mStaticLift = 0.0;
    mTargetHeight = 0.0;
    mIsActive = true;
    mBoostDirection = DIRECTION_OMNI_PLUS_X;
    mBoostDirection2 = DIRECTION_PLUS_X;
    mConditionType = 0;
    mConditionValue = 0;
    GameRuleDefinition::addDoubleAttribute((ConsoleGameRules::EGameRuleAttr_laps), &mLaps);
    GameRuleDefinition::addDoubleAttribute(ConsoleGameRules::EGameRuleAttr_liftForceModifier,
                                           &mLiftForceModifier);
    GameRuleDefinition::addDoubleAttribute(ConsoleGameRules::EGameRuleAttr_staticLift, &mStaticLift);
    GameRuleDefinition::addDoubleAttribute(ConsoleGameRules::EGameRuleAttr_targetHeight, &mTargetHeight);
    GameRuleDefinition::addIntAttribute(ConsoleGameRules::EGameRuleAttr_boostDirection, &mBoostDirection2);
    GameRuleDefinition::addIntAttribute(ConsoleGameRules::EGameRuleAttr_condition_type, &mConditionType);
    GameRuleDefinition::addIntAttribute(ConsoleGameRules::EGameRuleAttr_condition_value_0, &mConditionValue);
    dword_c4 = 0;
}

int ThermalAreaRuleDefinition::getActionType() {
    return 21;
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
        mBoostDirection = (eDirection)direction;
    }
}

void ThermalAreaRuleDefinition::WriteAttributesAsXML(std::string& xml) {
    if (!mName.empty())
        GameRuleDefinition::WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_slot, xml);

    if (mLaps != 1.0)
        GameRuleDefinition::WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_laps, xml);

    if (mLiftForceModifier != 0.0)
        GameRuleDefinition::WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_liftForceModifier, xml);

    if (mStaticLift != 0.0)
        GameRuleDefinition::WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_staticLift, xml);

    if (mTargetHeight != 0.0) {
        GameRuleDefinition::WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_targetHeight, xml);
        std::string str
            = formatstr(" boostDirection=\"%ls\"",
                        ThermalAreaRuleDefinition::DIRECTION_NAMES[(unsigned int)mBoostDirection]);
        xml.append(str);
    }

    if (mBoostDirection2) {
        GameRuleDefinition::WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_boostDirection, xml);
        GameRuleDefinition::WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_condition_type, xml);
        GameRuleDefinition::WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_condition_value_0, xml);
    }

    GameRuleDefinition::WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_x, xml);
    GameRuleDefinition::WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_y, xml);
    GameRuleDefinition::WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_z, xml);
    GameRuleDefinition::WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_x0, xml);
    GameRuleDefinition::WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_y0, xml);
    GameRuleDefinition::WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_z0, xml);

    if (dword_40)
        GameRuleDefinition::WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr_promptName, xml);
}

// NON_MATCHING: The branch for the first return true gets optimized
bool ThermalAreaRuleDefinition::getConditionsMet(std::shared_ptr<Entity> entity) {
    if (mBoostDirection2 == 0)
        return true;

    if (mBoostDirection2 == 1) {
        if (dword_c4 >= mConditionType)
            return false;
        return true;
    }

    if (mBoostDirection2 == 2) {
        if (entity->isType(ePlayer)) {
            MultiPlayerLevel* level = (MultiPlayerLevel*)(Minecraft::GetInstance()->mLevel);
            ClientScoreboard* scoreboard = level->GetClientScoreboard();
            std::shared_ptr<Player> player = std::static_pointer_cast<Player>(entity);

            int lapsCompleted = scoreboard->GetLapsCompleted(player->getSUID(), -1);
            if (lapsCompleted < mConditionType || lapsCompleted > mConditionValue)
                return false;
        }
    }

    return true;
}

void ThermalAreaRuleDefinition::resetConditions() {
    dword_c4 = 0;
}

void ThermalAreaRuleDefinition::updateUseCount() {
    ++dword_c4;
}

const int cDirectionX[4] = {1, -1, 0, 0};
const int cDirectionZ[4] = {0, 0, 1, -1};

bool ThermalAreaRuleDefinition::setBoostMods(int& xMultiplier, int& zMultiplier) {
    int dir = mBoostDirection;

    if (dir < (unsigned int)4) {
        xMultiplier = cDirectionX[dir];
        zMultiplier = cDirectionZ[dir];
        return true;
    }

    return false;
}

int ThermalAreaRuleDefinition::getBoostDirection() {
    return mBoostDirection;
}
