#pragma once

#include "types.h"
#include "net/minecraft/client/ui/scene/control/UIControl.h"
#include "net/minecraft/client/ui/scene/control/UIString.h"

class UIControl_Base : public UIControl {
public:
    UIControl_Base();

    ~UIControl_Base() override;
    bool setupControl(UIScene*, fuiRenderNode*, const std::string&) override;
    void tick() override;
    bool hasFocus() override;
    virtual void setLabel(UIString, bool, bool);
    virtual void setAllPossibleLabels(int, uint, wchar_t* [256]);

    UIString mUIString;
};
