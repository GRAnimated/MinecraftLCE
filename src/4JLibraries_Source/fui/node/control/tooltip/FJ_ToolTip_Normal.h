#pragma once

#include "FJ_ToolTip.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_ToolTip_Normal : public FJ_ToolTip {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
