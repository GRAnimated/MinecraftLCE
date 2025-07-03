#pragma once

#include "types.h"

class PlayerUID;
class PlayerTeam;
class StatsUID;

class Scoreboard {
public:
    virtual ~Scoreboard();
    virtual void ResetPlayerScores();
    virtual void removePlayerFromTeam(PlayerUID, PlayerTeam*);
    virtual void addPlayerToTeam(PlayerUID, PlayerTeam*);
    virtual void onTeamAdded(PlayerTeam*);
    virtual void onTeamChanged(PlayerTeam*);
    virtual void onTeamRemoved(PlayerTeam*);
    virtual void syncTeamChanges_0(PlayerTeam*);
    virtual void GetLastCheckpointID(const StatsUID&, int);
    virtual void GetLapsCompleted(const StatsUID&, int);
    virtual void GetEndZoneEntered(const StatsUID&, int);
    virtual void GetLastCheckpointSequenceID(const StatsUID&, int);

    char size[0x54];
};

ASSERT_SIZEOF(Scoreboard, 0x60)
