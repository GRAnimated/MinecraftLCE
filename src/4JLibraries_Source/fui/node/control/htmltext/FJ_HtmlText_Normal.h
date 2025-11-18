#pragma once

#include "4JLibraries_Source/fui/node/control/htmltext/FJ_HtmlText.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_HtmlText_Normal : public FJ_HtmlText {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
