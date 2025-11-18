#pragma once

#include "4JLibraries_Source/fui/node/control/button/list/scoreboard/FJ_ListButtonScoreBoard.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_ListButtonScoreBoard_Small : public FJ_ListButtonScoreBoard {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
