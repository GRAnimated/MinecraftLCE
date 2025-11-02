#pragma once

#include "FJ_EnchantingButton.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_EnchantingButton_Small : public FJ_EnchantingButton {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
