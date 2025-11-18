#pragma once

#include "4JLibraries_Source/fui/node/control/list/FJ_List.h"

class FJ_FuiNode;
class fuiRenderNode;

class FJ_List_ListButton : public FJ_List {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
