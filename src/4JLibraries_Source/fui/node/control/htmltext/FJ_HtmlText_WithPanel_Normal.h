#pragma once

#include "4JLibraries_Source/fui/node/control/htmltext/FJ_HtmlText_WithPanel.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_HtmlText_WithPanel_Normal : public FJ_HtmlText_WithPanel {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
