#pragma once

#include "fui/node/control/button/list/FJ_ListButton.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_ListButton_Small : public FJ_ListButton {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
