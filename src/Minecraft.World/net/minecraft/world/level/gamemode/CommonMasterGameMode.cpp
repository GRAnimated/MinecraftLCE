#include "net/minecraft/world/level/gamemode/CommonMasterGameMode.h"

#include "NX/Platform.h"
#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/client/eGameHostOption.h"
#include "net/minecraft/server/MinecraftServer.h"
#include "net/minecraft/world/level/LevelRuleset.h"
#include "net/minecraft/world/level/gamemode/ConsoleGameRules.h"
#include "net/minecraft/world/level/gamemode/Team.h"
#include "net/minecraft/world/level/gamemode/minigames/EMiniGameId.h"
#include "net/minecraft/world/level/gamemode/minigames/MiniGameDef.h"
#include "net/minecraft/world/level/gamemode/minigames/buildoff/WallGenerator.h"
#include "net/minecraft/world/level/gamemode/minigames/tumble/LayerGenerationRuleDefinition.h"
#include "net/minecraft/world/level/gamemode/minigames/tumble/TumbleGenerator.h"
#include "net/minecraft/world/level/levelgen/LevelGenerationOptions.h"
#include <vector>

long long CommonMasterGameMode::RestartMapGenerator() {
    EnterCriticalSection(&this->mMapGeneratorMutex);

    LevelRuleset* rules = CConsoleMinecraftApp::sInstance.getLevelGenerationOptions()->getRequiredGameRules();

    long long oldSeed = this->mMapGeneratorSeed;
    this->mMapGeneratorSeed = -1;
    Random random(oldSeed);

    EMiniGameId minigameId = CommonMasterGameMode::GetMiniGame()->GetId();
    if (minigameId == TUMBLE) {
        LayerGenerationRuleDefinition* layerGenRule = (LayerGenerationRuleDefinition*)rules->getRuleByType(
            ConsoleGameRules::EGameRuleType_LayerGeneration);

        const AABB* levelGenArea = rules->getNamedArea(L"LevelGeneration");

        delete this->mMapGenerator;

        Random layerRandom(oldSeed);
        std::vector<LayerGenerator*>* layers = layerGenRule->CreateLayers(
            layerRandom, levelGenArea, CommonMasterGameMode::GetMiniGame()->GetLayerCount(),
            this->mGenUnkFloat);

        this->mMapGenerator = (MapGenerator*)new TumbleGenerator(layerRandom, *layers);
        this->mMapGenerator->StartGeneration((Level*)this->GeneratorTargetLevel());

        delete layers;
    } else if (minigameId == BUILD_OFF) {
        std::vector<AABB*> walls1;
        rules->getNamedAreas(255, &walls1);

        std::vector<AABB*> walls2;
        rules->getNamedAreas(65280, &walls2);

        delete this->mMapGenerator;

        this->mMapGenerator = (MapGenerator*)new WallGenerator(random, &walls1, &walls2);
        this->mMapGenerator->StartGeneration((Level*)this->GeneratorTargetLevel());
    }

    LeaveCriticalSection(&this->mMapGeneratorMutex);
    return oldSeed;
}

const AABB* CommonMasterGameMode::GetTeamArea(Team* team) const {
    LevelGenerationOptions* options = CConsoleMinecraftApp::sInstance.getLevelGenerationOptions();
    LevelRuleset* rules = options->getRequiredGameRules();

    std::vector<AABB*> areas;
    rules->getNamedAreas(1 << team->getTeamIndex(), &areas);

    return areas.empty() ? nullptr : areas.at(0);
}

void CommonMasterGameMode::SetupMiniGameInstance(const MiniGameDef& def, int) {
    Minecraft::GetInstance()->SetupMiniGameInstance(const_cast<MiniGameDef&>(def), 0);
    MinecraftServer::getInstance()->setPvpAllowed(def.AllowPvp());
    XmlInt difficulty = def.getDifficulty();
    if (difficulty.hasValue())
        CConsoleMinecraftApp::sInstance.SetGameHostOption((eGameHostOption)0, difficulty.getValue());
}
