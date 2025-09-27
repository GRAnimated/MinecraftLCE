#pragma once

#include "fui/node/FJ_FuiNode.h"

#include <string>

class fuiRenderNode;

// nice spelling
/// STUB CLASS FOR FJ_Factory::initialise
class FJ_ExlamationMark : public FJ_FuiNode {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
