#pragma once

#include "net/minecraft/world/level/gamemode/CommonMasterGameMode.h"

class MasterGameMode : public CommonMasterGameMode {
public:
    ~MasterGameMode() override;
    void Tick() override;
    void RestartMapGenerator() override;
    void GetGameModeState() const override;
    void GeneratorTargetLevel() const override;
    void setChosenThemeWordId(int) override;
    void IsRoundPlaying() const override;
    void getScoreboard() const override;
    void GetSweptVolumeFromLastKnownPosition(std::shared_ptr<Player>) override;
    void GetLastCheckpointID(const StatsUID&) override;
    void OnCheckpointEnter(const std::shared_ptr<Player>&, unsigned int, CheckpointRuleDefinition*) override;
    void OnPrimaryTargetEnter(const std::shared_ptr<Player>&, TargetAreaRuleDefinition*) override;
    void OnSecondaryTargetEnter(const std::shared_ptr<Player>&, TargetAreaRuleDefinition*) override;
    void OnPowerupEnter(const std::shared_ptr<Player>&, unsigned int, PowerupRuleDefinition*) override;

    static void StaticCtor();
};
