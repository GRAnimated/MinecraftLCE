#pragma once

#include "FJ_List.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_List_MultiList : public FJ_List {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
