#pragma once

#include "4JLibraries_Source/fui/node/control/mobeffect/FJ_MobEffect.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_MobEffect_Small : public FJ_MobEffect {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
