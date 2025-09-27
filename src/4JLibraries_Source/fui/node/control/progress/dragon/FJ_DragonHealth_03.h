#pragma once

#include "FJ_DragonHealth.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_DragonHealth_03 : public FJ_DragonHealth {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
