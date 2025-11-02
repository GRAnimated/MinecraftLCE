#pragma once

#include "fui/node/control/list/FJ_List2D.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_List_ListButtonAchievement : public FJ_List2D {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
