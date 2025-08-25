#include "net/minecraft/world/level/gamemode/rules/GameRuleDefinition.h"

#include "java/io/File.h"
#include "net/minecraft/world/level/GameRule.h"
#include "net/minecraft/world/level/gamemode/GameRuleSaveInterface.h"
#include "net/minecraft/world/level/gamemode/minigames/glide/rules/TargetAreaRuleDefinition.h"

const wchar_t* ruleNames[] = {L"",
                              L"MapOptions",
                              L"ApplySchematic",
                              L"GenerateStructure",
                              L"GenerateBox",
                              L"PlaceBlock",
                              L"PlaceContainer",
                              L"PlaceSpawner",
                              L"BiomeOverride",
                              L"StartFeature",
                              L"AddItem",
                              L"AddEnchantment",
                              L"WeighedTreasureItem",
                              L"RandomItemSet",
                              L"DistributeItems",
                              L"WorldPosition",
                              L"LevelRules",
                              L"NamedArea",
                              L"ActiveChunkArea",
                              L"TargetArea",
                              L"ScoreRing",
                              L"ThermalArea",
                              L"PlayerBoundsVolume",
                              L"Killbox",
                              L"BlockLayer",
                              L"UseBlock",
                              L"CollectItem",
                              L"CompleteAll",
                              L"UpdatePlayer",
                              L"OnGameStartSpawnPositions",
                              L"OnInitialiseWorld",
                              L"SpawnPositionSet",
                              L"PopulateContainer",
                              L"DegradationSequence",
                              L"RandomDissolveDegrade",
                              L"DirectionalDegrade",
                              L"GrantPermissions",
                              L"AllowIn",
                              L"LayerGeneration",
                              L"LayerAsset",
                              L"AnyCombinationOf",
                              L"CombinationDefinition",
                              L"Variations",
                              L"BlockDef",
                              L"LayerSize",
                              L"UniformSize",
                              L"RandomizeSize",
                              L"LinearBlendSize",
                              L"LayerShape",
                              L"BasicShape",
                              L"StarShape",
                              L"PatchyShape",
                              L"RingShape",
                              L"SpiralShape",
                              L"LayerFill",
                              L"BasicLayerFill",
                              L"CurvedLayerFill",
                              L"WarpedLayerFill",
                              L"LayerTheme",
                              L"NullTheme",
                              L"FilterTheme",
                              L"ShaftsTheme",
                              L"BasicPatchesTheme",
                              L"BlockStackTheme",
                              L"RainbowTheme",
                              L"TerracottaTheme",
                              L"FunctionPatchesTheme",
                              L"SimplePatchesTheme",
                              L"CarpetTrapTheme",
                              L"MushroomBlockTheme",
                              L"TextureTheme",
                              L"SchematicTheme",
                              L"BlockCollisionException",
                              L"Powerup",
                              L"Checkpoint",
                              L"CustomBeacon",
                              L"ActiveViewArea"};

GameRuleDefinition::GameRuleDefinition() {
    mDescriptionName_ = L"";
    mPromptName = L"";
    mDataTag = 0;
    addStringAttribute(ConsoleGameRules::EGameRuleAttr_descriptionName, &mDescriptionName_);
    addStringAttribute(ConsoleGameRules::EGameRuleAttr_promptName, &mPromptName);
    addIntAttribute(ConsoleGameRules::EGameRuleAttr_dataTag, &mDataTag);
}

const AABB* GameRuleDefinition::getBoundingVolume() {
    return nullptr;
}

void GameRuleDefinition::moveBoundingVolume(int, int, int) {}

void GameRuleDefinition::writeAttributes(GameRuleSaveInterface* interface, unsigned int unk) {
    unsigned int count = 0;

    for (const auto& pair : mAttributeMap) {
        IGameRuleAttribute* attribute = pair.second;
        if (!attribute->isOptional() || attribute->hasValue()) {
            ++count;
        }
    }

    interface->startAttributes(count + unk);

    for (const auto& pair : mAttributeMap) {
        IGameRuleAttribute* attribute = pair.second;
        if (!attribute->isOptional() || attribute->hasValue()) {
            attribute->save(pair.first, interface);
        }
    }
}

void GameRuleDefinition::getChildren(std::vector<GameRuleDefinition*>*) {}

void GameRuleDefinition::getChildren(std::vector<GameRuleDefinition*>*, ConsoleGameRules::EGameRuleType) {}

GameRuleDefinition* GameRuleDefinition::addChild(ConsoleGameRules::EGameRuleType) {
    return nullptr;
}

void GameRuleDefinition::addAttribute(const std::wstring& str1, const std::wstring& str2) {
    ConsoleGameRules::EGameRuleAttr attrId = IGameRuleAttribute::attributeIdFromName(str1);
    if ((int)attrId != -1 && (int)attrId <= 90) {
        if (mAttributeMap.find(attrId) != mAttributeMap.end()) {
            auto& attribute = mAttributeMap[attrId];
            attribute->setValue(str2);
        }
    }
}

void GameRuleDefinition::onAttributesAdded() {}

void GameRuleDefinition::populateGameRule(GameRulesInstance::EGameRulesInstanceType instanceType,
                                          GameRule* gameRule) {
    GameRule::_ValueType valueType;
    valueType.field_8 = false;
    gameRule->setParameter(L"bComplete", valueType);
}

int GameRuleDefinition::getGoal() {
    return 0;
}

int GameRuleDefinition::getProgress(GameRule*) {
    return 0;
}

int GameRuleDefinition::getIcon() {
    return -1;
}

int GameRuleDefinition::getAuxValue() {
    return 0;
}

bool GameRuleDefinition::onUseBlock(GameRule*, int, int, int, int) {
    return false;
}

bool GameRuleDefinition::onCollectItem(GameRule*, not_null_ptr<ItemInstance>) {
    return false;
}

bool GameRuleDefinition::evaluateRule(Level*, LevelRuleset*, const MiniGameDef&) {
    return true;
}

void GameRuleDefinition::postProcessPlayer(std::shared_ptr<Player>) {}

void GameRuleDefinition::WriteXMLData(std::string& str) {
    int actionType = getActionType();
    if (actionType == 19) {
        if (((TargetAreaRuleDefinition*)this)->isPrimary())
            actionType = 19;
        else
            actionType = 20;
    }
    str.append(formatstr("<%ls", ruleNames[actionType]));
    WriteAttributesAsXML(str);
    str.append("/>\n");
}

void GameRuleDefinition::WriteAttributesAsXML(std::string& str) {
    WriteAllAttributesAsXML(str);
}

void GameRuleDefinition::WriteAllAttributesAsXML(std::string& str) {
    for (const auto& pair : mAttributeMap) {
        IGameRuleAttribute* attribute = pair.second;
        if (!attribute->isOptional() || attribute->hasValue()) {
            attribute->writeAsXml(pair.first, str);
        }
    }
}
