#pragma once

#include <string>

#include "fui/node/document/FJ_Document.h"

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_SaveMessage : public FJ_Document {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
