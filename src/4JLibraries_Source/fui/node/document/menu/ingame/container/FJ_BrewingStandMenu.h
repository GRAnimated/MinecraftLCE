#pragma once

#include "fui/node/document/container/FJ_AbstractContainerDocument.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_BrewingStandMenu : public FJ_AbstractContainerDocument {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
