#pragma once

#include "net/minecraft/world/level/gamemode/ConsoleGameRules.h"
#include <string>

class GameRuleSaveInterface;

class IGameRuleAttribute {
public:
    static const wchar_t* ATTRIBUTE_NAMES[91];

    IGameRuleAttribute();

    virtual ~IGameRuleAttribute();
    virtual void setValue(const std::wstring&);
    virtual void save(ConsoleGameRules::EGameRuleAttr, GameRuleSaveInterface*);
    virtual void writeAsXml(ConsoleGameRules::EGameRuleAttr, std::string&);

    void setOptional(bool optional);
    bool isOptional();
    bool hasValue();
    static ConsoleGameRules::EGameRuleAttr attributeIdFromName(const std::wstring&);

    bool m_isOptional = false;
    bool m_hasValue = false;
};
