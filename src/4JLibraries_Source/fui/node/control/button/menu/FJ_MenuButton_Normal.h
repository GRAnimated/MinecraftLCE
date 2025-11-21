#pragma once

#include "fui/node/control/button/menu/FJ_MenuButton.h"
#include <string>

class fuiRenderNode;
class FJ_FuiNode;

class FJ_MenuButton_Normal : public FJ_MenuButton {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);

    FJ_MenuButton_Normal(fuiRenderNode* node);
};
