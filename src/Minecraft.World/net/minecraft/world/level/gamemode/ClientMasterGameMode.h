#pragma once

#include "net/minecraft/world/level/gamemode/CommonMasterGameMode.h"
#include "types.h"

class ClientMasterGameMode : public CommonMasterGameMode {
public:
    ClientMasterGameMode();

    ~ClientMasterGameMode() override;
    void Tick() override;
    void OnExitedGame() override;
    void GetGameModeState() const override;
    void GeneratorTargetLevel() const override;
    void IsRoundPlaying() const override;
    void getScoreboard() const override;
    void ResetMapDistances() override;
    void GetSweptVolumeFromLastKnownPosition(std::shared_ptr<Player>) override;
    void GetLastCheckpointID(const StatsUID&) override;
    void OnProgressMade(const std::shared_ptr<Player>&, double) override;

    bool IsRoundRestarting();

    unsigned char size[0x2E0 - 8];
};

// yeah perfect time for random assert!
// ASSERT_SIZEOF(ClientMasterGameMode, 0x2E0)
