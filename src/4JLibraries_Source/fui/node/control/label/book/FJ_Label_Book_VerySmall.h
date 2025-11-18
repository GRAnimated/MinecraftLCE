#pragma once

#include "fui/node/control/label/book/FJ_Label_Book.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_Label_Book_VerySmall : public FJ_Label_Book {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
