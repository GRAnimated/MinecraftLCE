#pragma once
#include "string"

class fuiRenderNode;
class FJ_FuiNode;

class FJ_MenuButton_Small {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};