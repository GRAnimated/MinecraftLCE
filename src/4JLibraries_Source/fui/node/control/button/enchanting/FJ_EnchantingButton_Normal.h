#pragma once

#include "fui/node/control/button/enchanting/FJ_EnchantingButton.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_EnchantingButton_Normal : public FJ_EnchantingButton {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
