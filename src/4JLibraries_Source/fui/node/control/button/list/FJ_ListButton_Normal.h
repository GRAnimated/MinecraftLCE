#pragma once

#include "FJ_ListButton.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_ListButton_Normal : public FJ_ListButton {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
