#pragma once

#include "net/minecraft/client/ui/scene/control/UIControl_Base.h"

class UIControl_Cursor : public UIControl_Base {
public:
    UIControl_Cursor();

    bool setupControl(UIScene*, fuiRenderNode*, const std::string&) override;
};

static_assert(sizeof(UIControl_Cursor) == 0x68, "UIControl_Cursor Switch layout");
