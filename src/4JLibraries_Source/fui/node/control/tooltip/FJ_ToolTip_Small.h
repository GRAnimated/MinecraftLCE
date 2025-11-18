#pragma once

#include "4JLibraries_Source/fui/node/control/tooltip/FJ_ToolTip.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_ToolTip_Small : public FJ_ToolTip {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
