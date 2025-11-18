#pragma once

#include "net/minecraft/client/ui/scene/control/UIControl_Base.h"
#include "net/minecraft/client/ui/scene/control/UIString.h"

class UIControl_Label : public UIControl_Base {
public:
    UIControl_Label();

    void init(UIString);

    bool setupControl(UIScene*, fuiRenderNode*, const std::string&) override;

    bool byte68;
};
