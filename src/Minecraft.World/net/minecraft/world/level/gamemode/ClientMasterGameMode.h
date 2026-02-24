#pragma once

#include "net/minecraft/world/level/gamemode/CommonMasterGameMode.h"

enum EGameModeState {
    Init = 0,
    RoundEndingToLobby = 2,
    FinishVoting = 3,  // not sure about this one
    RoundWaitingToStart = 5,
    RoundStart = 6,
    RoundPlay = 7,
    RoundEnding = 9,
    NextRound = 10  // this or finish game, unsure
};

class ClientMasterGameMode : public CommonMasterGameMode {
public:
    ClientMasterGameMode();

    ~ClientMasterGameMode() override;
    void Tick() override;
    void OnExitedGame() override;
    void GetGameModeState() const override;
    ServerLevel* GeneratorTargetLevel() const override;
    void IsRoundPlaying() const override;
    void getScoreboard() const override;
    void ResetMapDistances() override;
    void GetSweptVolumeFromLastKnownPosition(std::shared_ptr<Player>) override;
    void GetLastCheckpointID(const StatsUID&) override;
    void OnProgressMade(const std::shared_ptr<Player>&, double) override;

    bool IsRoundRestarting();

    unsigned char m_size[0x2E0 - 8];
};

// yeah perfect time for random assert!
// ASSERT_SIZEOF(ClientMasterGameMode, 0x2E0)
