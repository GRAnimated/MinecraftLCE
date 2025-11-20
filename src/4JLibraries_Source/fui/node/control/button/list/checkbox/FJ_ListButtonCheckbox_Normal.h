#pragma once

#include "fui/node/control/button/list/checkbox/FJ_ListButtonCheckbox.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_ListButtonCheckbox_Normal : public FJ_ListButtonCheckbox {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
