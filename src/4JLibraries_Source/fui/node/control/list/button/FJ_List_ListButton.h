#pragma once

#include "fui/node/FJ_FuiNode.h"

class FJ_List_ListButton : public FJ_List {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
