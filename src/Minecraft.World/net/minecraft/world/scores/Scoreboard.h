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
    virtual void syncTeamChanges(PlayerTeam*);
    virtual int GetLastCheckpointID(const StatsUID&, int);
    virtual int GetLapsCompleted(const StatsUID&, int);
    virtual bool GetEndZoneEntered(const StatsUID&, int);
    virtual int GetLastCheckpointSequenceID(const StatsUID&, int);

    char m_size[0x54];
};

ASSERT_SIZEOF(Scoreboard, 0x60)
