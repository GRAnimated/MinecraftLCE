#pragma once

#include "fui/node/control/button/list/achievement/FJ_ListButtonAchievement.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_ListButtonAchievement_Small : public FJ_ListButtonAchievement {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
