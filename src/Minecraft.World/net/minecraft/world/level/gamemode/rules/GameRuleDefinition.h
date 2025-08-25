#pragma once

#include "types.h"
#include <string>
#include <unordered_map>
#include <vector>

#include "net/minecraft/world/level/gamemode/ConsoleGameRules.h"
#include "net/minecraft/world/level/gamemode/GameRulesInstance.h"
#include "net/minecraft/world/level/gamemode/IGameRuleAttribute.h"

class Player;
class MiniGameDef;
class LevelRuleset;
class Level;
class ItemInstance;
class GameRule;
class GameRuleSaveInterface;
class AABB;

class GameRuleDefinition {
public:
    GameRuleDefinition();

    virtual ~GameRuleDefinition();
    virtual ConsoleGameRules::EGameRuleType getActionType() = 0;
    virtual const AABB* getBoundingVolume();
    virtual void moveBoundingVolume(int, int, int);
    virtual void writeAttributes(GameRuleSaveInterface*, unsigned int);
    virtual void getChildren(std::vector<GameRuleDefinition*>*);
    virtual void getChildren(std::vector<GameRuleDefinition*>*, ConsoleGameRules::EGameRuleType);
    virtual GameRuleDefinition* addChild(ConsoleGameRules::EGameRuleType);
    virtual void addAttribute(const std::wstring&, const std::wstring&);
    virtual void onAttributesAdded();
    virtual void populateGameRule(GameRulesInstance::EGameRulesInstanceType, GameRule*);
    virtual int getGoal();               // unknown return type
    virtual int getProgress(GameRule*);  // unknown return type
    virtual int getIcon();
    virtual int getAuxValue();
    virtual bool onUseBlock(GameRule*, int, int, int, int);
    virtual bool onCollectItem(GameRule*, not_null_ptr<ItemInstance>);
    virtual bool evaluateRule(Level*, LevelRuleset*, const MiniGameDef&);
    virtual void postProcessPlayer(std::shared_ptr<Player>);
    virtual void WriteXMLData(std::string&);
    virtual void WriteAttributesAsXML(std::string&);

    void WriteAttributeAsXML(ConsoleGameRules::EGameRuleAttr, std::string&);
    void WriteAllAttributesAsXML(std::string&);

    void addStringAttribute(ConsoleGameRules::EGameRuleAttr, std::wstring*);
    void addDoubleAttribute(ConsoleGameRules::EGameRuleAttr, double*);
    void addIntAttribute(ConsoleGameRules::EGameRuleAttr, int*);
    void addHexAttribute(ConsoleGameRules::EGameRuleAttr, int*);

    void* field_8;
    std::wstring mDescriptionName_;
    std::wstring mPromptName;
    int mDataTag;
    std::unordered_map<ConsoleGameRules::EGameRuleAttr, IGameRuleAttribute*> mAttributeMap;
};
