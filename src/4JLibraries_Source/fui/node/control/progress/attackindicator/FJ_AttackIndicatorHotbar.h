#pragma once

#include "fui/node/control/progress/FJ_ProgressBar.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_AttackIndicatorHotbar : public FJ_ProgressBar {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
