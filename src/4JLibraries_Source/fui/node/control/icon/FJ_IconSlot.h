#pragma once

#include "fui/node/FJ_Base.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_IconSlot : public FJ_Base {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
