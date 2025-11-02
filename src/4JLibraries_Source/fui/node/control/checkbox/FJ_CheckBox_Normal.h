#pragma once

#include "FJ_Checkbox.h"

#include <string>

class fuiRenderNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_CheckBox_Normal : public FJ_Checkbox {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
