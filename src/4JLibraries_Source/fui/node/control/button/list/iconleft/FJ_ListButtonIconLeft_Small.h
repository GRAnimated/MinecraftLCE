#pragma once

#include "FJ_ListButtonIconLeft.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_ListButtonIconLeft_Small : public FJ_ListButtonIconLeft {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
