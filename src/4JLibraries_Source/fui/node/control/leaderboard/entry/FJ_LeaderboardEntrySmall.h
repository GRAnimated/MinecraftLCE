#pragma once

#include "fui/node/control/leaderboard/entry/FJ_LeaderboardEntry.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_LeaderboardEntrySmall : public FJ_LeaderboardEntry {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
