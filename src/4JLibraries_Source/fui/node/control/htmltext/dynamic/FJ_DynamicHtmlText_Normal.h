#pragma once

#include "4JLibraries_Source/fui/node/control/htmltext/dynamic/FJ_DynamicHtmlText.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_DynamicHtmlText_Normal : public FJ_DynamicHtmlText {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
