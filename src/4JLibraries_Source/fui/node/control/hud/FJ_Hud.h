#pragma once

#include "fui/node/FJ_FuiNode.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_Hud : public FJ_FuiNode {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
