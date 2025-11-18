#pragma once

#include "4JLibraries_Source/fui/node/control/button/list/FJ_ListButton.h"
#include <string>

class fuiRenderNode;
class FJ_FuiNode;

class FJ_ListButton_Medium : public FJ_ListButton {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
