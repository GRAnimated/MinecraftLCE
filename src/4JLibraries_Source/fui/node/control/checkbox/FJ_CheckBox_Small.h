#pragma once

#include "FJ_Checkbox.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_CheckBox_Small : public FJ_Checkbox {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
