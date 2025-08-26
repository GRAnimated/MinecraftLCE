#include "net/minecraft/world/level/gamemode/minigames/glide/rules/PowerupRuleDefinition.h"

#include "net/minecraft/world/level/gamemode/ConsoleGameRules.h"
#include "net/minecraft/world/level/gamemode/rules/AddItemRuleDefinition.h"
#include "net/minecraft/world/level/gamemode/rules/GameRuleDefinition.h"

PowerupRuleDefinition::PowerupRuleDefinition() : NamedAreaRuleDefinition() {}

PowerupRuleDefinition::~PowerupRuleDefinition() {}

ConsoleGameRules::EGameRuleType PowerupRuleDefinition::getActionType() {
    return ConsoleGameRules::EGameRuleType_Powerup;
}

void PowerupRuleDefinition::getChildren(std::vector<GameRuleDefinition*>* out) {
    for (auto it = this->mAddItemRules.begin(); it != this->mAddItemRules.end(); it++) {
        out->push_back((GameRuleDefinition*)*it);
    }
}

GameRuleDefinition* PowerupRuleDefinition::addChild(ConsoleGameRules::EGameRuleType type) {
    if (type != ConsoleGameRules::EGameRuleType_AddItem)
        return nullptr;

    GameRuleDefinition* childRule = new AddItemRuleDefinition();
    this->mAddItemRules.push_back((AddItemRuleDefinition*)childRule);
    return childRule;
}
