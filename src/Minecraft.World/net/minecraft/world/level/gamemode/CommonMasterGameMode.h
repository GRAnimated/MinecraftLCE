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

    std::vector<int>* GetPossibleVotes() { return &this->m_possibleVotes; }

    LevelGenerationOptions* m_generationOptions;
    void* m_qword10;
    void* m_qword18;
    void* m_qword20;
    void* m_qword28;
    void* m_qword30;
    void* m_qword38;
    void* m_qword40;
    void* m_qword48;
    void* m_qword50;
    void* m_qword58;
    void* m_qword60;
    long long m_mapGeneratorSeed;
    float m_genUnkFloat;
    MapGenerator* m_mapGenerator;
    nn::os::MutexType m_mapGeneratorMutex;
    void* m_qwordA0;
    void* m_qwordA8;
    void* m_qwordB0;
    std::vector<int> m_possibleVotes;
    void* m_qwordD0;
    Voteables* m_voteables;
    void* m_qwordE0;
    void* m_qwordE8;
    void* m_qwordF0;
    void* m_qwordF8;
    void* m_qword100;
    void* m_qword108;
    std::vector<AABB*> m_glideTargets;
    std::vector<CheckpointRuleDefinition*> m_glideCheckpoints;
    void* m_qword140;
    void* m_qword148;
    void* m_qword150;
    void* m_qword158;
    void* m_qword160;
    void* m_qword168;
    void* m_qword170;
    void* m_qword178;
};

ASSERT_SIZEOF(CommonMasterGameMode, 0x180)
