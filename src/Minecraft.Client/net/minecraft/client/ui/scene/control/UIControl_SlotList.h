#pragma once

#include "net/minecraft/client/ui/scene/control/UIControl_Base.h"

class UIControl_SlotList : public UIControl_Base {
public:
    bool setupControl(UIScene*, fuiRenderNode*, const std::string&) override;
    void addSlots(uint id, int count);

    int dword68;
};
