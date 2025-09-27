#pragma once

#include "fui/node/FJ_FuiNode.h"

class FJ_List_MenuButton : public FJ_FuiNode {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
