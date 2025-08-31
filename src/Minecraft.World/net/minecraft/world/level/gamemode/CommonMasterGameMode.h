#pragma once

#include "net/minecraft/world/entity/player/StatsUID.h"
#include "net/minecraft/world/level/gamemode/minigames/EMiniGameId.h"
#include "net/minecraft/world/level/gamemode/minigames/MapGenerator.h"
#include "net/minecraft/world/level/gamemode/minigames/Voteables.h"
#include "net/minecraft/world/level/gamemode/minigames/buildoff/WallGenerator.h"
#include "net/minecraft/world/level/levelgen/LevelGenerationOptions.h"
#include "net/minecraft/world/phys/AABB.h"
#include "nn/os/os_MutexTypes.h"
#include "types.h"
#include <memory>
#include <vector>

class CheckpointRuleDefinition;
class TargetAreaRuleDefinition;
class PowerupRuleDefinition;
class Player;
class MiniGameDef;
class Team;
class ServerLevel;

class CommonMasterGameMode {
public:
    virtual ~CommonMasterGameMode();
    virtual void Setup(EMiniGameId);
    virtual void Tick();
    virtual void OnExitedGame();
    virtual long long RestartMapGenerator();
    virtual void GetGameModeState() const = 0;
    virtual ServerLevel* GeneratorTargetLevel() const = 0;
    virtual void setChosenThemeWordId(int);
    virtual void IsRoundPlaying() const = 0;
    virtual void getScoreboard() const = 0;
    virtual void ResetMapDistances();
    virtual void CacheMapDistance();
    virtual void GetSweptVolumeFromLastKnownPosition(std::shared_ptr<Player>) = 0;
    virtual void GetLastCheckpointID(const StatsUID&) = 0;
    virtual void OnProgressMade(const std::shared_ptr<Player>&, double);
    virtual void OnLapCompleted(const std::shared_ptr<Player>&);
    virtual void OnCheckpointEnter(const std::shared_ptr<Player>&, unsigned int, CheckpointRuleDefinition*);
    virtual void OnTargetEnter(const std::shared_ptr<Player>&, unsigned int, TargetAreaRuleDefinition*);
    virtual void OnPrimaryTargetEnter(const std::shared_ptr<Player>&, TargetAreaRuleDefinition*);
    virtual void OnSecondaryTargetEnter(const std::shared_ptr<Player>&, TargetAreaRuleDefinition*);
    virtual void OnPowerupEnter(const std::shared_ptr<Player>&, unsigned int, PowerupRuleDefinition*);

    void CheckPowerups(const std::vector<std::shared_ptr<Player>>&);
    void setCheckpoints(std::vector<CheckpointRuleDefinition*>);
    const AABB* GetTeamArea(Team*) const;
    void SetupMiniGameInstance(const MiniGameDef&, int);
    void clearBuildOffVotes();

    static const MiniGameDef* GetMiniGame();

    std::vector<int>* GetPossibleVotes() { return &this->mPossibleVotes; }

    LevelGenerationOptions* mGenerationOptions;
    void* qword10;
    void* qword18;
    void* qword20;
    void* qword28;
    void* qword30;
    void* qword38;
    void* qword40;
    void* qword48;
    void* qword50;
    void* qword58;
    void* qword60;
    long long mMapGeneratorSeed;
    float mGenUnkFloat;
    MapGenerator* mMapGenerator;
    nn::os::MutexType mMapGeneratorMutex;
    void* qwordA0;
    void* qwordA8;
    void* qwordB0;
    std::vector<int> mPossibleVotes;
    void* qwordD0;
    Voteables* mVoteables;
    void* qwordE0;
    void* qwordE8;
    void* qwordF0;
    void* qwordF8;
    void* qword100;
    void* qword108;
    std::vector<AABB*> mGlideTargets;
    std::vector<CheckpointRuleDefinition*> mGlideCheckpoints;
    void* qword140;
    void* qword148;
    void* qword150;
    void* qword158;
    void* qword160;
    void* qword168;
    void* qword170;
    void* qword178;
};

ASSERT_SIZEOF(CommonMasterGameMode, 384)
