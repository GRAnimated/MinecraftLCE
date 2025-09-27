#pragma once

#include "FJ_ListButtonPlayerList.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_ListButtonPlayerList_Normal : public FJ_ListButtonPlayerList {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
