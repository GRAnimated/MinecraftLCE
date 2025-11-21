#pragma once

#include "fui/node/control/button/keyboard/FJ_KeyboardButtons.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_KeyboardButtons_Controls_Small : public FJ_KeyboardButtons {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
