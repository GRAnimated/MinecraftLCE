#pragma once

#include "fui/node/control/button/list/lobby/FJ_ListButtonLobby.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_ListButtonLobby_Normal : public FJ_ListButtonLobby {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
