#pragma once

#include <string>

#include "fui/node/control/label/FJ_Label.h"

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_Label_Html : public FJ_Label {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
