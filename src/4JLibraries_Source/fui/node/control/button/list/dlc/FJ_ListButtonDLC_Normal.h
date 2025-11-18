#pragma once

#include "4JLibraries_Source/fui/node/control/button/list/dlc/FJ_ListButtonDLC.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_ListButtonDLC_Normal : public FJ_ListButtonDLC {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
