#pragma once

#include "FJ_LeaderboardHeader.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_LeaderboardHeaderNormal : public FJ_LeaderboardHeader {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
