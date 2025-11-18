#pragma once

#include "4JLibraries_Source/fui/node/control/cursor/FJ_Cursor.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_Cursor_Normal : public FJ_Cursor {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
