#pragma once

#include "fui/node/control/button/list/scoreboard/FJ_ListButtonScoreBoard.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_ListButtonScoreBoard_Normal : public FJ_ListButtonScoreBoard {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
