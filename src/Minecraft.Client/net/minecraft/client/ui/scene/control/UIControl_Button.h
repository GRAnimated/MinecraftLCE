#pragma once

#include "net/minecraft/client/ui/scene/control/UIControl_Base.h"
#include "net/minecraft/client/ui/scene/control/UIString.h"
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

    bool m_focused = 0;
    bool m_couldBeEnabled = 0;
    bool m_enabled;
};
