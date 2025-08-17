#pragma once

#include <string>

#include "net/minecraft/world/level/gamemode/ConsoleGameRules.h"

class GameRuleSaveInterface {
public:
    GameRuleSaveInterface() {}

    virtual void startTag(ConsoleGameRules::EGameRuleType);
    virtual void startAttributes(int);
    virtual void saveAttribute(ConsoleGameRules::EGameRuleAttr, const std::wstring&);
    virtual void startChildren(int);
    virtual void finishTag();
};
