#pragma once

#include "fui/node/control/button/FJ_Button.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_LayoutButton : public FJ_Button {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
