#pragma once

#include "net/minecraft/client/tutorial/Tutorial.h"
#include "net/minecraft/world/level/gamemode/CommonMasterGameMode.h"

class BlockDegradeRoutine;
class GameStats;

class MasterGameMode : public CommonMasterGameMode {
public:
    enum ETimerID { GracePeriod = 3, ChestRefill = 5 };

    class CountdownInfo {
    public:
        CountdownInfo();

        int mInt_0;
        std::vector<int> mVector;
        void* fill[1];
        void (*mOnTimerFunc)(MasterGameMode*, void*);
        void (*mOnTimerFunc1)(MasterGameMode*, void*);
    };

    enum EInternalGameModeState {};

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

    void PopulateChests();
    void SetLockPlayerPositions(bool lock);
    void SetState(MasterGameMode::EInternalGameModeState);
    void sendTutorialUpdate(eTutorial_GameMode);
    void AddTimer(MasterGameMode::ETimerID, void (*)(MasterGameMode::ETimerID, MasterGameMode*, void*), void*,
                  int, int, int, int);
    bool StartTimer(MasterGameMode::ETimerID, MasterGameMode::CountdownInfo*);
    int GetTimerRemainingTime(MasterGameMode::ETimerID);
    void SetPlayersInvulnerable(bool);
    GameStats* GetGameStats();

    static void StaticCtor();
    static void OnGameStart(MasterGameMode* _this, void*);
    static void OnTimerCountdown(MasterGameMode::ETimerID, MasterGameMode*, void*);
    static void OnRefillChestTimer(MasterGameMode*, void*);
    static void OnGracePeriodEnd(MasterGameMode*, void*);

    void* fill78[78];
    BlockDegradeRoutine* mDegradeRoutine;
};
