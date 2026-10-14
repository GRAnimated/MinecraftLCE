#pragma once

#include "net/minecraft/client/ui/scene/control/UIControl_Base.h"

class UIControl_SlotList : public UIControl_Base {
public:
    UIControl_SlotList();

    bool setupControl(UIScene*, fuiRenderNode*, const std::string&) override;
    void ReInit() override;
    void setFocus(bool) override;
    void addSlots(uint id, int count);

    int m_dword68;
};

static_assert(sizeof(UIControl_SlotList) == 0x70, "UIControl_SlotList Switch layout");
