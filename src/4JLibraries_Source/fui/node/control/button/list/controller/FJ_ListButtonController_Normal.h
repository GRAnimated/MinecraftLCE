#pragma once

#include "fui/node/control/button/list/controller/FJ_ListButtonController.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_ListButtonController_Normal : public FJ_ListButtonController {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
