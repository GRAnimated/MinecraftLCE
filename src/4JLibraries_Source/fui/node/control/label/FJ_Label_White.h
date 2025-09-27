#pragma once

#include "FJ_Label.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_Label_White : public FJ_Label {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
