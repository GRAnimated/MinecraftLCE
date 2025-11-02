#pragma once

#include "fui/node/control/list/FJ_List.h"

class fuiRenderNode;

class FJ_List_MenuButton : public FJ_List {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
