#pragma once

#include "net/minecraft/world/PlayerUID.h"
#include <string>
#include <unordered_set>

class Team {
public:
    virtual ~Team();
    virtual bool isAlliedTo(Team*);
    virtual std::wstring getName() = 0;
    virtual std::wstring getFormattedName(const std::wstring&) = 0;
    virtual bool canSeeFriendlyInvisibles() = 0;
    virtual bool isAllowFriendlyFire() = 0;
    virtual int getNameTagVisibility() = 0;
    virtual int getTeamIndex() = 0;
    virtual int getDeathMessageVisibility() = 0;
    virtual std::unordered_set<PlayerUID> getPlayers() = 0;
};
