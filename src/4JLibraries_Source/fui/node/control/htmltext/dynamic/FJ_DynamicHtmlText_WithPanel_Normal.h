#pragma once

#include "FJ_DynamicHtmlText.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_DynamicHtmlText_WithPanel_Normal : public FJ_DynamicHtmlText {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
