#pragma once

#include "fui/node/control/textinput/FJ_TextInput.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_TextInput_Normal : public FJ_TextInput {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
