#pragma once

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_Label_HUD_BigWhite : public FJ_Label {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
