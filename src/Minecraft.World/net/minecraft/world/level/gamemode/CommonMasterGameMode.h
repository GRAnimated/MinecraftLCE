#pragma once

#include "net/minecraft/world/entity/player/StatsUID.h"
#include "net/minecraft/world/level/gamemode/minigames/EMiniGameId.h"
#include <memory>
#include <vector>

class CheckpointRuleDefinition;
class TargetAreaRuleDefinition;
class PowerupRuleDefinition;
class Player;

class CommonMasterGameMode {
public:
    virtual ~CommonMasterGameMode();
    virtual void Setup(EMiniGameId);
    virtual void Tick();
    virtual void OnExitedGame();
    virtual void RestartMapGenerator();
    virtual void GetGameModeState() const = 0;
    virtual void GeneratorTargetLevel() const = 0;
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
};
