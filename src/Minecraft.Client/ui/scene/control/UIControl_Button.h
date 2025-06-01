#pragma once

#include "Minecraft.Client/ui/scene/control/UIControl_Base.h"
#include "Minecraft.Client/ui/scene/control/UIString.h"
#include <cstdint>
class UIControl_Button : public UIControl_Base {
public:
    UIControl_Button();

    void setEnable(bool, bool);
    void init(UIString, int);

    bool setupControl(UIScene*, fuiRenderNode*, const std::string&) override;
    void tick() override;
    void ReInit() override;
    void setFocus(bool) override;

    bool mFocused = 0;
    bool mCouldBeEnabled = 0;
    bool mEnabled;
};