#pragma once

#include "4JLibraries_Source/fui/node/control/progress/dragon/FJ_DragonHealth.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_DragonHealth_02 : public FJ_DragonHealth {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
