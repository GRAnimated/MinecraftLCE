#pragma once

#include "FJ_UpsellButton.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_UpsellButton_Small : public FJ_UpsellButton {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
