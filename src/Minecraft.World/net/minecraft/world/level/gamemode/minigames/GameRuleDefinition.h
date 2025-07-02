#pragma once

#include "types.h"
#include <vector>

#include "Minecraft.World/level/gamemode/ConsoleGameRules.h"
#include "Minecraft.World/level/gamemode/GameRulesInstance.h"

class Player;
class MiniGameDef;
class LevelRuleset;
class Level;
class ItemInstance;
class GameRule;
class GameRuleSaveInterface;

class GameRuleDefinition {
public:
    virtual ~GameRuleDefinition();
    virtual void getActionType() = 0;
    virtual void getBoundingVolume();
    virtual void moveBoundingVolume(int, int, int);
    virtual void writeAttributes(GameRuleSaveInterface*, unsigned int);
    virtual void getChildren(std::vector<GameRuleDefinition*>*);
    virtual void getChildren(std::vector<GameRuleDefinition*>*, ConsoleGameRules::EGameRuleType);
    virtual void addChild(ConsoleGameRules::EGameRuleType);
    virtual void addAttribute(const std::wstring&, const std::wstring&);
    virtual void onAttributesAdded();
    virtual void populateGameRule(GameRulesInstance::EGameRulesInstanceType, GameRule*);
    virtual void getGoal();
    virtual void getProgress(GameRule*);
    virtual void getIcon();
    virtual void getAuxValue();
    virtual void onUseBlock(GameRule*, int, int, int, int);
    virtual void onCollectItem(GameRule*, not_null_ptr<ItemInstance>);
    virtual void evaluateRule(Level*, LevelRuleset*, const MiniGameDef&);
    virtual void postProcessPlayer(std::shared_ptr<Player>);
    virtual void WriteXMLData(std::string&);
    virtual void WriteAttributesAsXML(std::string&);
};
