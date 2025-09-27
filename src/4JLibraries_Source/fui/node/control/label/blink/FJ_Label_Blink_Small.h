#pragma once

#include "FJ_Label_Blink.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_Label_Blink_Small : public FJ_Label_Blink {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
