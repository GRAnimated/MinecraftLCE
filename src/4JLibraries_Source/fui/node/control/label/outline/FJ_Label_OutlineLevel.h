#pragma once

#include "FJ_LabelOutline.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_Label_OutlineLevel : public FJ_LabelOutline {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
