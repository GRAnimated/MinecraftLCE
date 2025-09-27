#pragma once

#include "string"

class fuiRenderNode;
class FJ_FuiNode;

// no typeinfo?????
class FJ_MCBREUpSell {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
