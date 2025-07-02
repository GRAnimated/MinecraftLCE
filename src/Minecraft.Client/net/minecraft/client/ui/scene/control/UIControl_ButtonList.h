#pragma once
#include "net/minecraft/client/ui/scene/control/UIControl_List.h"
#include <string>

class UIControl_ButtonList : public UIControl_List {
public:
    UIControl_ButtonList();

    void addItem(const std::wstring&, int);
    bool setupControl(UIScene*, fuiRenderNode*, const std::string&);
};