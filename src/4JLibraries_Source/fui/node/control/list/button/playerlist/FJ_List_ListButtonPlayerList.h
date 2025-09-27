#pragma once

#include "fui/node/FJ_FuiNode.h"

class FJ_List_ListButtonPlayerList : public FJ_List {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
